/*!
 * *******************************************************************************
 * @file WSSFM1XRX.c
 * @author julian bustamante
 * @version 1.5.6
 * @date Nov 18 , 2020
 * @brief Sigfox interface for the sigfox module. Interface
 * specific for module wisol SFM11R2D.
 *********************************************************************************/

/*NOTAS A CORREGIR-SOLO FORMATO-FUNCIONANDO MUY BIEN-NO OLVIDAR

-rsty rst2 cambiar nombres  
Si por algun motivo no responde el gettick, la no bloqueante se queda en waitting cambiar variables y agregarlas a una estructura para reiniciar la estructura en la plaicación en su momento??
Puede que pase...

 */

#include "wssfm1xrx.h"


/** Private Prototypes************************************************************************************************************************ */

/*Function to  wait response with delay*/
static WSSFM1XRX_Return_t WSSFM1XRX_WaitForResponse(WSSFM1XRXConfig_t *obj ,char *ExpectedResponse, WSSFM1XRX_WaitMode_t Wait, uint32_t msec );

/*Function to  transmit*/
static void WSSFM1XRX_StringTX(WSSFM1XRXConfig_t *obj, char* SigfoxString);

/*Function Limpia buffer y ready */
static void WSSFM1XRX_ResetObject(WSSFM1XRXConfig_t *obj);

/*Function arma trama deacuerdo a la estructura de datos 12 bytes*/
static void WSSFM1XRX_BuildFrame(char* str, void* data, uint8_t size);

/*Nible(4bits) decimal to hex string*/
char NibbletoX(uint8_t value);

/*Definitions Private**************************************************************************************************************************/

/*Maximo tamaño buffer char*/
#define WSSFM1XRX_MAX_DATA_SIZE 		25
/*Maximo tamaño buffer char*/
#define WSSFM1XRX_MAX_DATA_SIZE_WITH_DL 		37

/*Maximo tamaño trama hex string*/
#define	WSSFM1XRX_MAX_BYTE_TX_FRAME	12

/*Maximo tamaño buffer para las frecuencias*/
#define WSSFM1XRX_MAX_BUFF_FREQ		17


static char *WSSFM1XRX_UL_FREQUENCIES[6] ={
		"AT$IF=868130000\r",
		"AT$IF=902200000\r",
		"AT$IF=923200000\r",
		"AT$IF=920800000\r",
		"AT$IF=923300000\r",
		"AT$IF=865200000\r"
};

static char *WSSFM1XRX_DL_FREQUENCIES[6] ={
		"AT$DR=869525000\r",
		"AT$DR=905200000\r",
		"AT$DR=922200000\r",
		"AT$DR=922300000\r",
		"AT$DR=922300000\r",
		"AT$DR=866300000\r"
};

/*Public Functions*/

/**
 * @brief Function initialize the Wisol module.
 * @note Example :
 * 		SigfoxModule.StatusFlag = WSSFM1XRX_Init(&SigfoxModule, RSTCtrl_Sigfox, RST2Ctrl_Sigfox,
			APP_UART_C_SIGFOX,WSSFM1XRX_RCZ4, qSchedulerGetTick,BufferRxFrame,sizeof(BufferRxFrame),4);
 * @param obj Structure containing all data from the Sigfox module.
 * @param ...
 * @return Operation result in the form WSSFM1XRX_Return_t.
 */
WSSFM1XRX_Return_t WSSFM1XRX_Init(WSSFM1XRXConfig_t *obj, DigitalFcn_t Reset, DigitalFcn_t WkUp, TxFnc_t Tx_Wssfm1xrx,WSSFM1XRX_FreqUL_t Frequency_Tx ,TickReadFcn_t TickRead,char* Input , uint8_t SizeInput, uint8_t MaxNumberRetries){
	WSSFM1XRX_Return_t RetValue = WSSFM1XRX_INIT_OK;

	if( ( NULL != obj ) && ( NULL != Reset ) && ( NULL != WkUp ) && ( NULL != Tx_Wssfm1xrx ) && ( NULL != TickRead ) ){ /*si alguno es null, return falla*/
        obj->RST=Reset;
        obj->WKUP=WkUp;
        obj->TX_WSSFM1XRX=Tx_Wssfm1xrx;
        obj->TICK_READ = TickRead;
        obj->RxReady=SF_FALSE;
        obj->RxIndex=0;
        obj->Frequency=Frequency_Tx;
        obj->RxFrame = Input; 
        obj->SizeBuffRx = SizeInput;
        obj->State_Api = WSSFM1XRX_IDLE; /**/
        obj->State_W = WSSFM1XRX_W_IDLE; /*State Idle function Wait non blocking*/
        (void)memset((void*)obj->RxFrame,0,obj->SizeBuffRx);
        obj->MaxNumberRetries = MaxNumberRetries;
    }
	else{
		RetValue = WSSFM1XRX_FAILURE;
	}
    return RetValue;
}

/*WSSFM1XRX_*/



/**
 * @brief Function delay non blocking.
 * @note  the function GetTick_ms must be initialized to work
 * @note Example :
 * 			WSSFM1XRX_Wait_NonBlock(&obj,500);
 * @param obj Structure containing all data from the Wisol module.	
 * @param msec time to wait in mili second.
 * @return Operation result in the form WSSFM1XRX_Return_t:
 * 			<< WSSFM1XRX_TIMEOUT >> if the time has expired
 * 			<< WSSFM1XRX_WAITING >> if the time has not expired
 */
WSSFM1XRX_Return_t WSSFM1XRX_Wait_NonBlock(WSSFM1XRXConfig_t *obj, uint32_t msec){
	static WSSFM1XRX_Return_t RetValue;
	static volatile uint32_t WSSFM1XRX_StartTick = 0;
	if( WSSFM1XRX_W_IDLE == obj->State_W ){
		RetValue = WSSFM1XRX_WAITING ;
		WSSFM1XRX_StartTick = 0;
		WSSFM1XRX_StartTick = obj->TICK_READ() ;/*tickRead_ms();*/
		obj->State_W = WSSFM1XRX_W_RUNNING ;
	}

	if( ( obj->TICK_READ() - WSSFM1XRX_StartTick) > msec ){ 
		obj->State_W = WSSFM1XRX_W_IDLE;
		obj->State_Api = WSSFM1XRX_IDLE; /*Cuando vence el tiempo mando el comando de nuevo*/
		RetValue = WSSFM1XRX_TIMEOUT ;
	}
	else{
		RetValue = WSSFM1XRX_WAITING;
	}
	return RetValue;

}

/**
 * @brief Function delay blocking.
 * @note  the function GetTick_ms must be initialized to work
 * @note Example :
 * 			WSSFM1XRX_Wait_Block(&obj,500);
 * @param obj Structure containing all data from the Wisol module.	
 * @param msec time to wait in mili second.
 * @return Operation result in the form WSSFM1XRX_Return_t:
 * 			<< WSSFM1XRX_TIMEOUT >> if the time has expired
 */
WSSFM1XRX_Return_t WSSFM1XRX_Wait_Block(WSSFM1XRXConfig_t *obj, uint32_t msec){
	while( WSSFM1XRX_WAITING == WSSFM1XRX_Wait_NonBlock(obj, msec) ){}
	return WSSFM1XRX_TIMEOUT ;
}

/**
 * @brief Function set low power the Wisol module.
 * @note Example :
 *		WSSFM1XRX_Sleep(&SigfoxConfig,(WSSFM1XRX_WaitMode_t)WSSFM1XRX_Wait_Block);
 * @param obj Structure containing all data from the Wisol module.
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @return WSSFM1XRX_Return_t.
 * 			 WSSFM1XRX_OK_RESPONSE or  WSSFM1XRX_TIMEOUT or WSSFM1XRX_WAITING
 */
WSSFM1XRX_Return_t WSSFM1XRX_Sleep(WSSFM1XRXConfig_t *obj ,WSSFM1XRX_WaitMode_t Wait ){
	obj->RST(1);
	obj->WKUP(1);
	return WSSFM1XRX_SendRawMessage(obj,"AT$P=2\r","OK",NULL,Wait,WSSFM1XRX_SLEEP_TIME_DELAY_RESP); 

}
/**
 * @brief Function wakeup from pin extern the Wisol module.
 * @note Example :
 * 		WSSFM1XRX_WakeUP(&SigfoxModule,Wait);
 * @param obj Structure containing all data from the Wisol module.
 * @param Wait Pointer to function delay blocking  of type WSSFM1XRX_WaitMode_t
 * @return void.
 */
WSSFM1XRX_Return_t WSSFM1XRX_WakeUP(WSSFM1XRXConfig_t *obj) {
	static WSSFM1XRX_Return_t RetValue = WSSFM1XRX_NONE;
	static WSSFM1XRX_Return_t RetValueAux = WSSFM1XRX_NONE;  
	if( WSSFM1XRX_NONE ==  RetValueAux ) {
		obj->RST(SF_FALSE);
		obj->WKUP(SF_FALSE);
		RetValueAux = WSSFM1XRX_WAITING;
	}
	RetValue =  WSSFM1XRX_Wait_Block(obj, WSSFM1XRX_WAKEUP_TIME_DELAY_PULSE); /*Return WAITING or TIMEOUT*/

	if( WSSFM1XRX_TIMEOUT == RetValue ){
		obj->RST(SF_TRUE);
		obj->WKUP(SF_TRUE);
		RetValueAux = WSSFM1XRX_NONE;
	}
	/*Wait after exit low-power mode*/
	RetValue =  WSSFM1XRX_Wait_Block(obj, WSSFM1XRX_WAKEUP_WAIT_TIME_DELAY_RESP); /*Return WAITING or TIMEOUT*/
	return  RetValue;
}



/**
 * @brief Function reset Wisol module.
 * @note Example :
 * 		WSSFM1XRX_ResetModule(&SigfoxModule,Wait);
 * @param obj Structure containing all data from the Wisol module.
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @return  WSSFM1XRX_WAITING or WSSFM1XRX_NONE or WSSFM1XRX_TIMEOUT
 */
WSSFM1XRX_Return_t WSSFM1XRX_ResetModule(WSSFM1XRXConfig_t *obj ,WSSFM1XRX_WaitMode_t Wait  ){

	static WSSFM1XRX_Return_t RetValue = WSSFM1XRX_NONE, RetValueAux = WSSFM1XRX_NONE;
	if( WSSFM1XRX_NONE == RetValueAux ){
		WSSFM1XRX_ResetObject(obj);
		obj->RST(SF_FALSE);  /*Reset*/
		obj->WKUP(SF_FALSE);  /*Wake up*/
		RetValueAux = WSSFM1XRX_WAITING;
	}
	RetValue =  Wait(obj,WSSFM1XRX_SLEEP_TIME_RESET); /*Return WAITING or TIMEOUT*/

	if( WSSFM1XRX_TIMEOUT == RetValue ){
		obj->RST(SF_TRUE);
		obj->WKUP(SF_TRUE);
		RetValueAux = WSSFM1XRX_NONE;
	}
	/*Wait despues de salir del modo de bajo consumo*/
	return  RetValue;
}


/**
 * @brief Function check module sending AT command to the Wisol module.
 * @note Example :
 * 		WSSFM1XRX_CheckModule(&SigfoxModule,Wait);
 * @param obj Structure containing all data from the Sigfox module.
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @return WSSFM1XRX_Return_t.
 * 			<< WSSFM1XRX_OK_RESPONSE >> If response expected is the correct
 * 			WSSFM1XRX_OK_RESPONSE or  WSSFM1XRX_TIMEOUT or WSSFM1XRX_WAITING
 */
WSSFM1XRX_Return_t WSSFM1XRX_CheckModule(WSSFM1XRXConfig_t *obj,WSSFM1XRX_WaitMode_t Wait ){
	return WSSFM1XRX_SendRawMessage(obj,"AT\r","OK",NULL,Wait,WSSFM1XRX_GENERAL_TIME_DELAY_RESP); 
}

/**
 * @brief Function get ID unique from Wisol module.
 * @note Example :
 * 		WSSFM1XRX_GetID(&SigfoxModule,wait,ID);
 * @param obj Structure containing all data from the Sigfox module.
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @param IDStr Buffer for copy string ID
 * @return WSSFM1XRX_Return_t
 * 			WSSFM1XRX_OK_RESPONSE
 * 			WSSFM1XRX_TIMEOUT
 * 			WSSFM1XRX_WAITING
 */
WSSFM1XRX_Return_t WSSFM1XRX_GetID(WSSFM1XRXConfig_t *obj,WSSFM1XRX_WaitMode_t Wait,char *IDStr){
	return 	WSSFM1XRX_GetRespNoexpected(obj,Wait,"AT$I=10\r",IDStr);

	/*return NULL;*/
}

/**
 * @brief Function get PAC unique from Wisol module.
 * @note Example :
 * 		WSSFM1XRX_GetID(&SigfoxModule,wait,PAC);
 * @param obj Structure containing all data from the Sigfox module.
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @param PACStr Buffer for copy string PAC
 * @return WSSFM1XRX_Return_t
 * 			WSSFM1XRX_OK_RESPONSE
 * 			WSSFM1XRX_TIMEOUT
 * 			WSSFM1XRX_WAITING
 */
WSSFM1XRX_Return_t WSSFM1XRX_GetPAC(WSSFM1XRXConfig_t *obj,WSSFM1XRX_WaitMode_t Wait,char *PACStr ){
	return 	WSSFM1XRX_GetRespNoexpected(obj,Wait,"AT$I=11\r",PACStr);
}


/**
 * @brief Function get supply Voltage  from Wisol module.
 * @note Example :
 * 		WSSFM1XRX_GetVolts(&SigfoxModule,Wait);
 * @param obj Structure containing all data from the Sigfox module.
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @param mVolt pointer to variable for store mili voltage
 * @return WSSFM1XRX_Return_t
 * 			WSSFM1XRX_OK_RESPONSE
 * 			WSSFM1XRX_TIMEOUT
 * 			WSSFM1XRX_WAITING
 */
WSSFM1XRX_Return_t WSSFM1XRX_GetVoltage(WSSFM1XRXConfig_t *obj, WSSFM1XRX_WaitMode_t Wait,uint16_t *mVolt ){
	char mVolStr[10]; /*Stored stringmV*/
	char *ptr = NULL;
	WSSFM1XRX_Return_t RetValue;

	RetValue =	WSSFM1XRX_GetRespNoexpected(obj,Wait,"AT$V?\r",mVolStr);
	*mVolt = (uint16_t)strtol(mVolStr , &ptr ,BASE_DECIMAL);
	return RetValue;
}

/**
 * @brief Function Send command to the Wisol module.
 * @note  Example : WSSFM1XRX_SendRawMessageWaitResponse("AT$SF=aabbcc1122","OK",Wait)
 * @param obj Structure containing all data from the Sigfox module.
 * @param Payload containing string to transmitions at Wisol module.
 * @param ExpectedResponse expectedResponse expected Response from module Wisol .
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @param msec time to wait in mili second.
 * @return WSSFM1XRX_OK_RESPONSE or  WSSFM1XRX_TIMEOUT or WSSFM1XRX_WAITING
 *  @Note : use only if  response expected
 */
WSSFM1XRX_Return_t WSSFM1XRX_SendRawMessage(WSSFM1XRXConfig_t *obj,char* Payload,char* ExpectedResponse,char * BuffStr,WSSFM1XRX_WaitMode_t Wait,uint32_t msec){

	WSSFM1XRX_Return_t RetValue = WSSFM1XRX_NONE;
	if( WSSFM1XRX_IDLE == obj->State_Api ){ /*Firstentry bloqueante o no bloqueante*/
		WSSFM1XRX_ResetObject(obj);
		if( NULL != Payload ) {
			WSSFM1XRX_StringTX(obj,Payload);
		}
		obj->State_Api = WSSFM1XRX_RUNNING;
		if(obj->NumberRetries++ > obj->MaxNumberRetries) {
			obj->NumberRetries = 0;
			RetValue = WSSFM1XRX_MAX_RETRIES_REACHED; /* misra c 15.5*/
		}

	}
	/*expected is confirmed in to WSSFM1XRX_WaitForResponse*/
	if( WSSFM1XRX_MAX_RETRIES_REACHED == RetValue ){
		/*compliant misra c 15.5*/
	}
	else{
		RetValue = WSSFM1XRX_WaitForResponse(obj,ExpectedResponse,Wait,msec);
	}
	


	/*para que funcione block or non block*/
	if( (WSSFM1XRX_TIMEOUT == RetValue) || (WSSFM1XRX_OK_RESPONSE == RetValue) ){ /*misra c 12.1*/
		if( (uint8_t)SF_TRUE == obj->RxReady ){ /*misra c 14.4*/
			if( NULL != BuffStr ){  /*misra c 15.6*/
				(void)strcpy(BuffStr, (char*)obj->RxFrame) ; /*misra c 17.7*/
			}
			obj->NumberRetries = 0;
		}
		obj->State_Api = WSSFM1XRX_IDLE;
	}
	return RetValue;
}


/**
 * @brief Function ask channels of the transceiver.
 * @note Example :
 * 		WSSFM1XRX_AskChannels(&SigfoxModule);
 * @param obj Structure containing all data from the Sigfox module.
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @return WSSFM1XRX_OK_RESPONSE or  WSSFM1XRX_TIMEOUT or WSSFM1XRX_WAITING
 */
WSSFM1XRX_Return_t WSSFM1XRX_AskChannels(WSSFM1XRXConfig_t *obj,WSSFM1XRX_WaitMode_t Wait, WSSFM1XRX_Channels_t *Channels ){
	WSSFM1XRX_Return_t RetVal ;
	char* rspPtr;
	RetVal = WSSFM1XRX_SendRawMessage(obj,"AT$GI?\r",NULL,NULL,Wait,WSSFM1XRX_GENERAL_TIME_DELAY_RESP);

	if( WSSFM1XRX_OK_RESPONSE == RetVal ){ 
		rspPtr = strchr( ((const char *)obj->RxFrame) , (int)',');
		if( NULL != rspPtr ){
			Channels->x = (uint8_t)obj->RxFrame[0]- (uint8_t)'0';/* (*(rspPtr-1))-(uint8_t)'0';*/ /*non compliant misra c 18.4*/
			Channels->y = (uint8_t)obj->RxFrame[2] -(uint8_t)'0' ;  /* (*(rspPtr+1))-(uint8_t)'0';  */
		}
	}
	return RetVal;
}

/**  Revisar DOC-------- 
 * @brief Function verificate c hannels of the transceiver.
 * @note Example :
 * 		WSSFM1XRX_CheckChannels(&SigfoxModule);
 * @param obj Structure containing all data from the Sigfox module.
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @return Operation result in the form WSSFM1XRX_Return_t.
 * 			WSSFM1XRX_CHANN_NO_OK   : se debe resetear canales
 *			WSSFM1XRX_CHANN_OK      : No se resetea canales
 */
/*hacer getchannels */
WSSFM1XRX_Return_t WSSFM1XRX_CheckChannels(WSSFM1XRXConfig_t *obj, WSSFM1XRX_WaitMode_t Wait ){
	WSSFM1XRX_Channels_t Channels ={0,0};
	WSSFM1XRX_Return_t retval;
	retval = WSSFM1XRX_AskChannels(obj,Wait,&Channels);
	if( WSSFM1XRX_OK_RESPONSE == retval ){
		/*misra c 10.4 & 12.1*/
		retval = ( (Channels.x == (uint8_t)0) || (Channels.y < (uint8_t)3 )) ? WSSFM1XRX_CHANN_NO_OK : WSSFM1XRX_CHANN_OK;
	}
	return retval;
}

/**
 * @brief Function reset channels from Wisol module.
 * @note Example :
 * 		WSSFM1XRX_ResetChannels(&SigfoxModule, Wait);
 * @param obj Structure containing all data from the Sigfox module.
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @return WSSFM1XRX_Return_t.
 * 			<< WSSFM1XRX_OK_RESPONSE >> If response expected is the correct
 * 			or WSSFM1XRX_WAITING or WSSFM1XRX_TIMEOUT
 **/
WSSFM1XRX_Return_t WSSFM1XRX_ResetChannels(WSSFM1XRXConfig_t *obj, WSSFM1XRX_WaitMode_t Wait ){

	return WSSFM1XRX_SendRawMessage(obj,"AT$RC\r","OK",NULL,Wait,WSSFM1XRX_GENERAL_TIME_DELAY_RESP); 
}

/**
 * @brief Function change frequency uplink from Sigfox module.
 * @note Example :
 * 		WSSFM1XRX_ChangeFrequencyUL(&SigfoxModule,Wait,WSSFM1XRX_RCZ4);
 * @param obj Structure containing all data from the Wisol module.
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @param Frequency frequency trasmission type WSSFM1XRX_FreqUL_t
 * @return WSSFM1XRX_Return_t.
 * 			<< WSSFM1XRX_OK_RESPONSE >> If response expected is the correct
 * 			or WSSFM1XRX_WAITING or WSSFM1XRX_TIMEOUT
 * */
WSSFM1XRX_Return_t WSSFM1XRX_ChangeFrequencyUL(WSSFM1XRXConfig_t *obj,WSSFM1XRX_WaitMode_t Wait , WSSFM1XRX_FreqUL_t Frequency){	
	/*misra c 11.8*/
	return WSSFM1XRX_SendRawMessage(obj, 
                                         (char*)WSSFM1XRX_UL_FREQUENCIES[Frequency]  ,
                                        "OK",NULL,Wait,WSSFM1XRX_GENERAL_TIME_DELAY_RESP); 
}

/**
 * @brief Function change frequency Downlink from Sigfox module.
 * @note Example :
 * 		WSSFM1XRX_ChangeFrequencyDL(&SigfoxModule,Wait,WSSFM1XRX_RCZ4);
 * @param obj Structure containing all data from the Wisol module.
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @param Frequency frequency receive type WSSFM1XRX_FreqUL_t
 * @return WSSFM1XRX_Return_t.
 * 			<< WSSFM1XRX_OK_RESPONSE >> If response expected is the correct
 * 			or WSSFM1XRX_WAITING or WSSFM1XRX_TIMEOUT
 * */
WSSFM1XRX_Return_t WSSFM1XRX_ChangeFrequencyDL(WSSFM1XRXConfig_t *obj,WSSFM1XRX_WaitMode_t Wait , WSSFM1XRX_FreqUL_t Frequency){
	return WSSFM1XRX_SendRawMessage(obj, (char *)WSSFM1XRX_DL_FREQUENCIES[Frequency]  ,"OK",NULL,Wait,WSSFM1XRX_GENERAL_TIME_DELAY_RESP);
}

/**
 * @brief Function ask frequency uplink from Wisol module.
 * @note Example :
 * 		WSSFM1XRX_AskFrequencyUL(&SigfoxModule, Wait);
 * @param obj Structure containing all data from the Sigfox module.
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @param Frequency pointer to variable for store Frequency
 * @return   WSSFM1XRX_Return_t  WSSFM1XRX_OK_RESPONSE
 * */

WSSFM1XRX_Return_t WSSFM1XRX_AskFrequencyUL(WSSFM1XRXConfig_t *obj,WSSFM1XRX_WaitMode_t Wait, WSSFM1XRX_FreqUL_t *Frequency ){
	WSSFM1XRX_Return_t RetValue;
	uint8_t i;
	uint8_t FreqStr[11] = {(uint8_t)'\0'}; /*misra c 12.3*/

	RetValue =	WSSFM1XRX_GetRespNoexpected(obj,Wait,"AT$IF?\r",(char*)FreqStr);

	if( strlen((char*)FreqStr) >= 9 ){  /*length frequency incomming*/
		for(i = 0; i< (uint8_t)6; i++) { /*misra c 10.4*/
			if( NULL != strstr(WSSFM1XRX_UL_FREQUENCIES[i], (const char*)FreqStr) ){
				break;
			}
		}
		*Frequency = (WSSFM1XRX_FreqUL_t)i;
	}
	return RetValue;
}

/**
 * @brief Function save parameter in the flash memory from Sigfox module.
 * @note Example :
 * 		WSSFM1XRX_SaveParameters(&SigfoxModule,Wait);
 * @param obj Structure containing all data from the Wisol module.
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @return Operation result in the form WSSFM1XRX_Return_t
 * 			<< WSSFM1XRX_OK_RESPONSE >> If response expected is the correct
 * 			or WSSFM1XRX_WAITING or WSSFM1XRX_TIMEOUT
 * */
WSSFM1XRX_Return_t WSSFM1XRX_SaveParameters(WSSFM1XRXConfig_t *obj, WSSFM1XRX_WaitMode_t Wait ){
	return WSSFM1XRX_SendRawMessage(obj,"AT$WR\r","OK",NULL,Wait,WSSFM1XRX_GENERAL_TIME_DELAY_RESP); 
}


/**
 * @brief Function send message frame in string hexadecimal to sigfox module.
 * 	@note Example :
 * 		x = WSSFM1XRX_SendMessage(&SigfoxModule,Wait,&iButton_Data,Buffer_Tx,MAX_SIZE_IBUTTON_DATA,SigfoxModule.DownLink);
 * 
 * @param obj Structure containing all data from the Sigfox module.
 * @param Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @param data Structure containing frame to send the Sigfox module.
 * @param CopyDataTx buffer for trasmission of message, size minimun 37 bytes
 * @param size number of bytes in the payload. less o equal to 12 bytes.
 * @param eDownlink downlink enable o disable (0/1)
 * 
 * @return Operation result in the form WSSFM1XRX_Return_t
 * 			<< WSSFM1XRX_OK_RESPONSE >> If response expected is the correct
 * 			or WSSFM1XRX_WAITING or WSSFM1XRX_TIMEOUT
 *
 */
WSSFM1XRX_Return_t WSSFM1XRX_SendMessage(WSSFM1XRXConfig_t *obj,WSSFM1XRX_WaitMode_t Wait, void* data, void * CopyDataTx, uint8_t size, uint8_t eDownlink){
	uint8_t slen = ((uint8_t)2*size) + (uint8_t)6; /*misra c 10.4 & 12.1*/
	char UplinkPayload[WSSFM1XRX_MAX_DATA_SIZE_WITH_DL] = "AT$SF="; /*max length frame with downlink*/
	uint32_t timeWait;
	WSSFM1XRX_BuildFrame(&UplinkPayload[6], data, size); /*no compliant misra c 18.4*/
	if(( WSSFM1XRX_IDLE == obj->State_Api )) {
		obj->DownLink = eDownlink;	/*misra c 15.6*/
	}

	if( (uint8_t)SF_TRUE == obj->DownLink){ /*misra c 14.4*/
		UplinkPayload[slen]=',';
		slen++;						/*misra c 13.3*/
		UplinkPayload[slen]='1';
		slen++;
		UplinkPayload[slen]='\r';
	}
	else{
		UplinkPayload[slen]='\r';
	}

	timeWait = (bool)eDownlink ? (uint32_t)WSSFM1XRX_DL_TIMEOUT : (uint32_t)WSSFM1XRX_SEND_MESSAGE_TIME_DELAY_RESP; /*WSSFM1XRX_DL_TIMEOUT*/
	if( NULL != CopyDataTx ) {
		(void)memcpy(CopyDataTx,UplinkPayload,WSSFM1XRX_MAX_DATA_SIZE_WITH_DL);
	}
	return WSSFM1XRX_SendRawMessage(obj, UplinkPayload, "OK", NULL, Wait, timeWait);
}

/**
 * @brief Function ISR UART receive incoming frame to Wisol module.
 * @note Example :
 * 		SigfoxISRRX(&SigfoxModule,RxChar);    call in the  interrup serial
 * the buffer is stored in the structure obj->RxFrame.
 * 
 * @param obj Structure containing all data from the Sigfox module.
 * @param RxChar char received by uart
 * @return void.
 */
void WSSFM1XRX_ISRRX(WSSFM1XRXConfig_t *obj, const char RxChar){

	/* misra c 15.5*/
	if( (RxChar < (char)CHAR_PRINT_BELOW)  || (RxChar > (char)CHAR_PRINT_ABOVE) ) {
		return ;  /*Char no print*/
	}

	/*misra c 15.6,14.4 , 15.6*/
	if((uint8_t)SF_TRUE == obj->RxReady) {
		return; /* B_uffer reveived*/
	}
	obj->RxFrame[obj->RxIndex] = RxChar; /*misra c 13.3*/
	obj->RxIndex++;

	if (obj->RxIndex >= (obj->SizeBuffRx - (uint8_t)1) ) { /* misra c 10.4*/
		obj->RxIndex=0; 
	}
	obj->RxFrame[obj->RxIndex] = (char)0;
	if( '\r' == RxChar ){
		/*  Check if there is a downlink request */
		if((uint8_t)SF_FALSE == obj->DownLink){
			obj->RxIndex = 0;
			obj->RxReady = SF_TRUE; /* Framed completed*/
		}else{	/*misra c 15.6*/
			obj->DownLink = SF_FALSE; /* Clear the downlink request */
		}
	}
}


/**
 * @brief Function verificate response received from Wisol module.
 * @note Example :
 * 		if(WSSFM1XRX_MatchResponse(&SigfoxModule,"OK") == WSSFM1XRX_OK_RESPONSE) {}
 * @param obj Structure containing all data from the Sigfox module.
 * @param expectedResponse expected Response from module sigfox .
 * 
 * @return Operation result in the form WSSFM1XRX_Return_t.
 * 			<< WSSFM1XRX_OK_RESPONSE >> If response expected is the correct
 * 			<< WSSFM1XRX_RSP_NOMATCH >> If response expected is not correct 
 */

WSSFM1XRX_Return_t WSSFM1XRX_MatchResponse(WSSFM1XRXConfig_t *obj, char *expectedResponse){
	WSSFM1XRX_Return_t Rprocess = WSSFM1XRX_RSP_NOMATCH;
	if((bool)obj->RxReady){
		if( NULL != expectedResponse ){
			if( NULL != strstr((const char *) obj->RxFrame,(char *)expectedResponse) ) {
				Rprocess = WSSFM1XRX_OK_RESPONSE;
			}
			else{
				Rprocess = WSSFM1XRX_RSP_NOMATCH;
			}
		}
		else{ 
			Rprocess = WSSFM1XRX_OK_RESPONSE;
		}
	}
	return Rprocess;
}

/** Call if downlink is active
 * @brief Function to discriminate downlink frames.
 * @param obj Structure containing the incoming frame from the Sigfox module.
 * @return Operation result in the form WSSFM1XRX_DL_Return_t.
 */
WSSFM1XRX_DL_Return_t DL_DiscriminateDownLink(WSSFM1XRXConfig_t* obj){
	uint8_t* payLoadHead;
	uint8_t* payLoadTail;
	uint8_t byteIndex = WSSFM1XRX_DL_BYTES_OFFSET;
	/* uint8_t numericFrame[WSSFM1XRX_DL_PAYLOAD_SYZE];*/
	uint8_t byteStr[WSSFM1XRX_DL_BYTE_SIZE + 1] = {0};
	WSSFM1XRX_DL_Return_t RetValue  = WSSFM1XRX_DL_UNKNOWN;
	/* Get payload offset */
	payLoadHead = (uint8_t *)strstr((const char*)obj->RxFrame, "RX");

	if(NULL == payLoadHead){
		return WSSFM1XRX_DL_HEAD_ERROR;
    }
	/* Check payload length */
	payLoadTail = (uint8_t *)strstr((const char*)payLoadHead, "\r");

	if(NULL == payLoadTail){
		return WSSFM1XRX_DL_TAIL_ERROR;
    }
    payLoadTail[1] = (uint8_t)'\0';
	if( WSSFM1XRX_DL_PAYLOAD_LENGTH != (strlen((const char *)payLoadHead) - 1u) ){ /*probar*/
		return WSSFM1XRX_DL_LENGTH_ERROR;
    }
	/* Convert frame to numeric values */
	uint8_t i;
	for( i = 0; i < (uint8_t)WSSFM1XRX_DL_PAYLOAD_SYZE; i++){
		/* Copy byte strings an convert them to numbers */
		(void)strncpy((char *)byteStr, (const char *)&payLoadHead[byteIndex], WSSFM1XRX_DL_BYTE_SIZE);/*probar*/
		obj->DL_NumericFrame[i] = (uint8_t)strtol((const char *)byteStr, NULL, 16);
		byteIndex += (uint8_t)WSSFM1XRX_DL_BYTES_OFFSET;
		RetValue = WSSFM1XRX_DL_SUCCESS;
	}

	/*Deprecated return ( NULL != obj->CallbackDownlink )? obj->CallbackDownlink(obj) : WSSFM1XRX_DL_DISCRIMINATE_ERROR;*/
	return RetValue;
}

/*Private Functions ********************************************************************************************************************************/
static void WSSFM1XRX_StringTX(WSSFM1XRXConfig_t *obj, char* WSSFM1XRX_String){
  	int i =0;
  	while( '\0' != WSSFM1XRX_String[i]  ) {          
		obj->TX_WSSFM1XRX(NULL,WSSFM1XRX_String[i++]);
	}
}

/*Private Functions ***********************************************************************************************************************************************/
static void WSSFM1XRX_ResetObject(WSSFM1XRXConfig_t *obj){
	(void)memset( (void *) obj->RxFrame,0,obj->SizeBuffRx);
	obj->StatusFlag=(uint8_t)WSSFM1XRX_DEFAULT;
	obj->RxIndex=0;
	obj->RxReady=SF_FALSE;
	obj->State_Api = WSSFM1XRX_IDLE; /*verificar*/
	obj->State_W = WSSFM1XRX_W_IDLE; /*verificar*/
}


/*Private Functions*/

/**
 * @brief Function order the frame.
 */
static void WSSFM1XRX_BuildFrame(char* str, void* data, uint8_t size){
	int8_t  i;
	int8_t  j = 0;   
	uint8_t xbyte;
	uint8_t finalsize;
	uint8_t *bdata = data; /*desviation misra c 11.5*/
    uint8_t sizecopy;
    sizecopy = size;
	sizecopy = (sizecopy > (uint8_t)WSSFM1XRX_MAX_BYTE_TX_FRAME )? (uint8_t)WSSFM1XRX_MAX_BYTE_TX_FRAME : sizecopy;
        
	finalsize = sizecopy*((uint8_t)2);
	str[finalsize]='\0';
        
	for(i = ((int8_t)sizecopy-1) ; i >= 0; i--){   /*misra 10.4 */
		xbyte = bdata[i];
		str[j++]=NibbletoX(xbyte>>4);
		str[j++]=NibbletoX(xbyte);
	}
}

/**
 * @brief Function wait for response expected.
 */
static WSSFM1XRX_Return_t WSSFM1XRX_WaitForResponse(WSSFM1XRXConfig_t *obj , char *ExpectedResponse, WSSFM1XRX_WaitMode_t Wait ,uint32_t msec){
	WSSFM1XRX_Return_t retvalue;
    WSSFM1XRX_Return_t retvalueM ;  /*= WSSFM1XRX_NONE;*/
	retvalue =  Wait(obj,msec); /*Return WAITING or TIMEOUT*/
	retvalueM = WSSFM1XRX_MatchResponse(obj,ExpectedResponse); /*Return Response ok or No match*/
	return (retvalueM == WSSFM1XRX_OK_RESPONSE)? retvalueM  : retvalue  ;/*Delay NonBlocking or Non-blocking*/
}


/*Nible(4bits) decimal to hex string***/

char NibbletoX(uint8_t value){
	char ch;
    uint8_t c_h;
	c_h = (value & (uint8_t)0x0Fu) + (uint8_t)'0' ;
    ch = (char)c_h;
	return (ch > (char)'9')? (ch + 7) : ch;
}


/**
 * @brief function aux send command and wait to sigfox module.
 * @param obj Structure containing all data from the Sigfox module.
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @param CommandStr Pointer to char *  containing Command AT to send the Sigfox module.
 * @param BuffStr Pointer to char *  to store the response of the sigfox module.
 * 
 * @return Operation result in the form WSSFM1XRX_DL_Return_t.
 *
 * @Note : use only if not response expected
 */
WSSFM1XRX_Return_t WSSFM1XRX_GetRespNoexpected(WSSFM1XRXConfig_t *obj,WSSFM1XRX_WaitMode_t Wait, char * CommandStr, char *BuffStr){
	WSSFM1XRX_Return_t RetValue;
    bool RxReady_nonvolatile; /* asignar obj->ready no actualiza en test*/

	if( ( WSSFM1XRX_IDLE == obj->State_Api ) ) { /*Firstentry block or Nonblocking*/
		WSSFM1XRX_ResetObject(obj);
		WSSFM1XRX_StringTX(obj,CommandStr);
		obj->State_Api = WSSFM1XRX_RUNNING;
	}
	RetValue = Wait(obj,WSSFM1XRX_GENERAL_TIME_DELAY_RESP) ;
	RxReady_nonvolatile = (bool)obj->RxReady; /*corrige regla misra c - no colocar en inicializar*/
	
	if( (WSSFM1XRX_TIMEOUT == RetValue) || ((RetValue == WSSFM1XRX_WAITING) && ( RxReady_nonvolatile )  ) ){
		if( RxReady_nonvolatile ){  
            if( NULL != BuffStr ) {
            	(void)strcpy((char*)BuffStr, (char*)obj->RxFrame) ; /*frame stored in RxFrame*/ 
            }
			RetValue = WSSFM1XRX_OK_RESPONSE;
		}
		else{
            RetValue = WSSFM1XRX_FAILURE;
        }
		obj->State_Api = WSSFM1XRX_IDLE;
	}
	return RetValue;
}
