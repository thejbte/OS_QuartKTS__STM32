/*!
 * *******************************************************************************
 * @file Task_Service_Sigfox.h
 * @author Esp.Ing.Julian Bustamante N
 * @version 1.2.5
 * @date Jan  7, 2021
 * @brief Sigfox service interface for the sigfox module
 *********************************************************************************/


#include <Task_Service_Sigfox.h>



/** Buffer Rx Frame for module sigfox*/
static char BufferRxFrame[WSSFM1XRX_BUFF_RX_FRAME_LENGTH];

/** Buffer Tx Frame*/
static char BufferTxFrame[WSSFM1XRX_BUFF_TX_FRAME_LENGTH];

typedef struct {
	qTask_t *PtrToTaskFSM;
	WSSFM1XRX_FreqUL_t FreqInFlash;
	uint8_t Repeat;
	uint8_t StatusDownlink; /*if recv*/
}Object_t;

static Object_t obj;

/*task for service*/
static qTask_t Task_UplinkDispatcher;
static qTask_t Task_SigFox_Service;  			 /*!< Solo esta es publica*/
static qQueue_t SigFox_UplinkQueue;

static WSSFM1XRXConfig_t SigfoxModule;

static WSSFM1XRX_FreqUL_t Frequency = 0xff; /*store freq ask*/

static SigFox_Info_t SigFoxData;


void Service_Sigfox_Run(uint8_t enable){

	qTask_Set_State(&Task_SigFox_Service, (enable == 1 ? qEnabled : qDisabled ) );
}

void Service_Sigfox_ISRHandler(const char rxchar){
	WSSFM1XRX_ISRRX(&SigfoxModule,rxchar);
}

/*after qSchedulerSetup*/
void Service_Sigfox_Setup(WSSFM1XRX_FreqUL_t DefaultConfigRC , DigitalFcn_t Reset, DigitalFcn_t WkUp , TxFnc_t SigfoxPutc , TickReadFcn_t GetTick){
	SigfoxModule.StatusFlag = WSSFM1XRX_Init(&SigfoxModule,
			Reset, WkUp, SigfoxPutc, DefaultConfigRC, GetTick,
			BufferRxFrame, sizeof(BufferRxFrame), 4);

	static uint8_t UplinkQueueMessage_Stack[MAX_NUM_ELEMENT_ENQUEUE*sizeof(Service_SigfoxRequest_t)]={0};
	qQueue_Setup(&SigFox_UplinkQueue, UplinkQueueMessage_Stack, sizeof(Service_SigfoxRequest_t), MAX_NUM_ELEMENT_ENQUEUE);

	qOS_Add_Task(&Task_SigFox_Service, Service_Sigfox_Callback, qMedium_Priority, 0.01, qPeriodic, qDisabled, NULL);
	qOS_Add_EventTask(&Task_UplinkDispatcher, Service_Sigfox_UplinkDispatcher_Callback, qHigh_Priority, NULL);
	qTask_Attach_Queue(&Task_UplinkDispatcher, &SigFox_UplinkQueue, qQUEUE_COUNT, 1);
}


/**
 * @brief This function Initialize SigFox service
 * @param PtrToTaskFSM pointer to task FSM where controller service
 * @param FreqInFlash Data read from microcontroller flash
 * @param Enable run service (1 or 0)
 * */
void Service_Sigfox_Init(qTask_t *PtrToTaskFSM , uint16_t FreqInFlash, uint8_t Enable , uint8_t repeat){
	obj.PtrToTaskFSM = PtrToTaskFSM;
	obj.FreqInFlash = FreqInFlash;
	obj.Repeat = repeat;
	obj.StatusDownlink=0;
	Service_Sigfox_ClearReadyToUpLink();
	Service_Sigfox_ResetStatus();
	Service_Sigfox_Run(Enable);
}

/**
 * @brief This function Get Actual state of SigFox service
 * @return  Actual state
 * */
WSSFM1XRX_Service_Status_t Service_Sigfox_GetStatus(void){
	return SigFoxData.WilsolService_Status;
}

/**
 * @brief This function Clear Actual state of SigFox service
 * */
void Service_Sigfox_ResetStatus(void){ /*module not Initialized*/
	SigFoxData.WilsolService_Status = WSSFM1XRX_STATUS_MODULE_NOT_INITIALIZED;
}


/**
 * @brief This function Set Actual state of SigFox service
 * */
static void Service_Sigfox_SetStatus(WSSFM1XRX_Service_Status_t status){
	SigFoxData.WilsolService_Status = status;
}


/**
 * @brief This function Get battery from sigfox module
 * @return  battery in mv
 * * */
uint16_t Service_Sigfox_GetBattery(void){
	Service_Sigfox_WakeUp();
	WSSFM1XRX_GetVoltage(&SigfoxModule,WSSFM1XRX_Wait_Block,&SigFoxData.VBatt );
	return SigFoxData.VBatt;
}

/**
 * @brief This function Get ID from sigfox module
 * @return  pointer to char -> string ID
 * * */
char* Service_Sigfox_GetID(void){
	static SigFox_Info_t SFData;
	strcpy(SFData.ID,SigFoxData.ID);
	return SFData.ID; /*cambiar a static, punteroal salir de la funcion*/
}

/**
 * @brief This function Get PAC from sigfox module
 * @return  pointer to char -> string PAC
 * * */
char* Service_Sigfox_GetPAC(void){

	static SigFox_Info_t SFData;
	strcpy(SFData.PAC,SigFoxData.PAC);
	return SFData.PAC;
}

/**
 * @brief This function get frequency from sigfox module
 * @return WSSFM1XRX_FreqUL_t enum frequency
 * @note if module yet not being initialized this return
 *       frequency stored in microcontroller flash or freq default
 * */
WSSFM1XRX_FreqUL_t Service_Sigfox_GetFreqUpLink(void){

	obj.FreqInFlash = ( (obj.FreqInFlash != 0) && (obj.FreqInFlash < MAX_NUMBER_SIGFOX_FREQUENCY ) ) ? obj.FreqInFlash : SigfoxModule.Frequency;   /*flash arranca en 0 o 0xff al estar vacio*/
	/*return 0xff si aun no esta iicializado*/

	if(Frequency > MAX_NUMBER_SIGFOX_FREQUENCY )
		Frequency = obj.FreqInFlash;
	return Frequency;
}

/**
 * @brief This function get frame transmitted
 * @param pointer to string frame
 * @note: Only used after send message
 * * */
char* Service_Sigfox_GetFrameSend(){
	return BufferTxFrame;
}


/**
 * @brief This function Get flag ready to uplink initialized
 * @return  int 0 or 1
 * * */
int Service_Sigfox_GetReadyToUpLink(void){
	return SigFoxData.ReadyToUplink;
}


/**
 * @brief This function clear flag ready to uplink
 * * */
void Service_Sigfox_ClearReadyToUpLink(void){
	SigFoxData.ReadyToUplink = 0;
}

/**
 * @brief This function send message - enqueue message
 * * */
//void Service_Sigfox_Send( Service_SigfoxRequest_t *Service_SigfoxRequest){
//qQueue_SendToBack(&SigFox_UplinkQueue, Service_SigfoxRequest);
//}

void Service_Sigfox_Send( uint8_t *data, uint8_t downlink){
	static Service_SigfoxRequest_t Service_SigfoxRequest;
	memcpy(Service_SigfoxRequest.Payload, data,12);  /*add repeticiones*/
	Service_SigfoxRequest.Request = ((downlink == 1) ? REQUEST_SEND_PAYLOAD_DOWNLINK : REQUEST_SEND_PAYLOAD);
	if(obj.Repeat){   /*flag  isactive repeat*/
		qQueue_SendToBack(&SigFox_UplinkQueue, &Service_SigfoxRequest);

		Service_SigfoxRequest.Request =  REQUEST_SEND_PAYLOAD;  /*downlink solo en una vez */
		qQueue_SendToBack(&SigFox_UplinkQueue, &Service_SigfoxRequest);
	}else{
		qQueue_SendToBack(&SigFox_UplinkQueue, &Service_SigfoxRequest);
	}
}




WSSFM1XRX_Return_t Service_Sigfox_WakeUp(void){
	WSSFM1XRX_Return_t ret;
	ret =  WSSFM1XRX_WakeUP(&SigfoxModule);
	WSSFM1XRX_Wait_Block(&SigfoxModule,1.0);
	return ret;
}

WSSFM1XRX_Return_t Service_Sigfox_Sleep(void){
	return  WSSFM1XRX_Sleep(&SigfoxModule,WSSFM1XRX_Wait_NonBlock);
}

WSSFM1XRX_Return_t Service_Sigfox_Reset(void){
	return WSSFM1XRX_ResetModule(&SigfoxModule, WSSFM1XRX_Wait_Block);
}

uint8_t* Service_Sigfox_GetDownlinkFrame(void){
	static uint8_t Downlink_NumericFrame[WSSFM1XRX_DL_PAYLOAD_SYZE];
	memcpy(Downlink_NumericFrame, (char*)SigfoxModule.DL_NumericFrame , sizeof(SigfoxModule.DL_NumericFrame));
	return Downlink_NumericFrame;
}

uint8_t Service_Sigfox_GetDownlinkStatus(void){
	return obj.StatusDownlink;
}

WSSFM1XRX_DL_Return_t Service_Sigfox_DownlDiscriminate(void){
	return DL_DiscriminateDownLink(&SigfoxModule) ;
}


uint8_t Service_Sigfox_QueueIsEmpty(void){
	return qQueue_IsEmpty(&SigFox_UplinkQueue);
}

/**
 * @brief API function for change frequency
 * @param Freq: frquency uplink ( WSSFM1XRX_RCZ4 or WSSFM1XRX_RCZ2)
 * */
void Service_Sigfox_ChangeFrequency(WSSFM1XRX_FreqUL_t Freq){
	static Service_SigfoxRequest_t Service_SigfoxRequest;

	Service_SigfoxRequest.Frequency = Freq;
	Service_SigfoxRequest.Request = REQUEST_CHANGE_FREQUENCY;
	qTask_Set_State(&Task_SigFox_Service, qEnabled);  						 /* así por que waituntil suelta la corutina y se acaba el tasksendevent*/
	qTask_Notification_Send(&Task_SigFox_Service, &Service_SigfoxRequest);
}


/**
 * @brief This callback is Dispatcher Payload
 * @param evendata
 * */
void Service_Sigfox_UplinkDispatcher_Callback(qEvent_t e){
	static WSSFM1XRX_Return_t ret;
	static Service_SigfoxRequest_t *Service_SigfoxRequest;

	qCR_Begin{
		qDebug_Message("Coroutine from Beginning Dispatcher");
		if(e->Trigger == byQueueCount && SigFoxData.ReadyToUplink){
			Service_SigfoxRequest = (Service_SigfoxRequest_t*)qQueue_Peek(e->EventData);

			if(Service_SigfoxRequest->Request == REQUEST_SEND_PAYLOAD || Service_SigfoxRequest->Request == REQUEST_SEND_PAYLOAD_DOWNLINK){
				Service_Sigfox_SetStatus(WSSFM1XRX_STATUS_CHK_CHANNELS);

				Service_SigfoxDebugDecimal(_VERBOSE_,Service_Sigfox_GetStatus());

				qCR_WaitUntil( (ret = WSSFM1XRX_CheckChannels(&SigfoxModule, WAIT ))  == WSSFM1XRX_CHANN_OK || (ret == WSSFM1XRX_CHANN_NO_OK) || (ret == WSSFM1XRX_MAX_RETRIES_REACHED) );
				if(  ret == WSSFM1XRX_CHANN_NO_OK   ){
					qCR_WaitUntil( (WSSFM1XRX_OK_RESPONSE ==  (ret = WSSFM1XRX_ResetChannels(&SigfoxModule,WAIT) )) || (WSSFM1XRX_MAX_RETRIES_REACHED == ret ) );
					if(WSSFM1XRX_MAX_RETRIES_REACHED == ret){
						WSSFM1XRX_ResetModule(&SigfoxModule,WSSFM1XRX_Wait_Block);
						qCR_Restart;
					}
					Service_Sigfox_SetStatus(WSSFM1XRX_STATUS_RST_CHANNELS);

					Service_SigfoxDebugDecimal(_VERBOSE_,Service_Sigfox_GetStatus());

				}else if(WSSFM1XRX_MAX_RETRIES_REACHED == ret){
					WSSFM1XRX_ResetModule(&SigfoxModule,WSSFM1XRX_Wait_Block);
					qCR_Restart;
				}

				Service_Sigfox_SetStatus(WSSFM1XRX_STATUS_SEND_MESSAGE);

				Service_SigfoxDebugDecimal(_VERBOSE_,Service_Sigfox_GetStatus());

				qCR_WaitUntil( WSSFM1XRX_OK_RESPONSE == (ret = WSSFM1XRX_SendMessage(&SigfoxModule,WAIT,Service_SigfoxRequest->Payload ,BufferTxFrame , MAX_SIZE_IBUTTON_DATA,Service_SigfoxRequest->Request)) ||
						((ret == WSSFM1XRX_TIMEOUT) && (	Service_SigfoxRequest->Request == REQUEST_SEND_PAYLOAD_DOWNLINK) ) || (ret == WSSFM1XRX_MAX_RETRIES_REACHED ) );

				/*solo reintenta sin downlink- con downlink no es necesario por que puede ser señal y no falla del modulo*/
				if(WSSFM1XRX_MAX_RETRIES_REACHED == ret){
					WSSFM1XRX_ResetModule(&SigfoxModule,WSSFM1XRX_Wait_Block);
					qCR_Restart;
				}
				if(WSSFM1XRX_DL_SUCCESS == DL_DiscriminateDownLink(&SigfoxModule)){
					obj.StatusDownlink = 1;
					qDebug_Memory(SigfoxModule.DL_NumericFrame,WSSFM1XRX_DL_PAYLOAD_SYZE);
				}else{
					obj.StatusDownlink = 0;
					memset(SigfoxModule.DL_NumericFrame,0,WSSFM1XRX_DL_PAYLOAD_SYZE);  /*No downlink*/
				}

				Service_Sigfox_SetStatus(WSSFM1XRX_STATUS_SENT_MESSAGE);
				qQueue_RemoveFront(e->EventData);
				if(obj.PtrToTaskFSM != NULL)
					qTask_Notification_Send(obj.PtrToTaskFSM,(void*)WSSFM1XRX_STATUS_SENT_MESSAGE);

				Service_SigfoxDebugDecimal(_VERBOSE_,Service_Sigfox_GetStatus());
				qDebug_Message(BufferTxFrame);
				qDebug_Message("WSSFM1XRX_SENT_MESSAGE");
			}
		}
		qCR_Yield;
	}qCR_End;
}
/**
 * @brief This function run service in backgroud
 * @param evendata
 * */
void Service_Sigfox_Callback(qEvent_t e){
	static WSSFM1XRX_Return_t ret;
	Service_SigfoxRequest_t *Service_SigfoxRequest;
	static WSSFM1XRX_FreqUL_t RCZ;
	static Service_SigfoxRequest_t request;

	Service_SigfoxRequest = (Service_SigfoxRequest_t*)e->EventData;
	if(e->Trigger == byNotificationSimple &&	( Service_SigfoxRequest->Request == REQUEST_CHANGE_FREQUENCY)){
		request.Request = Service_SigfoxRequest->Request;
		request.Frequency = Service_SigfoxRequest->Frequency;
	}

	qCR_Begin{
		qDebug_Message("Coroutine from Beginning");
		Service_Sigfox_SetStatus(WSSFM1XRX_STATUS_WKUP);

		Service_SigfoxDebugDecimal(_VERBOSE_,Service_Sigfox_GetStatus());


		qCR_WaitUntil(WSSFM1XRX_TIMEOUT == ( ret = WSSFM1XRX_WakeUP(&SigfoxModule)) );

		//qCR_Delay(1.0);

		Service_Sigfox_SetStatus(WSSFM1XRX_STATUS_CHK_MODULE);

		Service_SigfoxDebugDecimal(_VERBOSE_,Service_Sigfox_GetStatus());

		qCR_WaitUntil( ( WSSFM1XRX_OK_RESPONSE == (ret = WSSFM1XRX_CheckModule(&SigfoxModule, WAIT)) )  || (WSSFM1XRX_MAX_RETRIES_REACHED == ret)  );

		if(WSSFM1XRX_MAX_RETRIES_REACHED  == ret ){
			WSSFM1XRX_ResetModule(&SigfoxModule,WSSFM1XRX_Wait_Block);
			qCR_Restart;
		}
		Service_Sigfox_SetStatus(WSSFM1XRX_STATUS_GET_VOLTAGE);

		Service_SigfoxDebugDecimal(_VERBOSE_,Service_Sigfox_GetStatus());

		qCR_WaitUntil( (WSSFM1XRX_OK_RESPONSE == (ret = WSSFM1XRX_GetVoltage(&SigfoxModule,WAIT,&SigFoxData.VBatt ) )) || (WSSFM1XRX_FAILURE == ret) );
		if(WSSFM1XRX_FAILURE  == ret ){
			WSSFM1XRX_ResetModule(&SigfoxModule,WSSFM1XRX_Wait_Block);
			qCR_Restart;
		}
		Service_SigfoxDebugDecimal(_VERBOSE_,SigFoxData.VBatt);
		/*ask channels*/
		Service_Sigfox_SetStatus(WSSFM1XRX_STATUS_ASK_FREQ_UL);

		Service_SigfoxDebugDecimal(_VERBOSE_,Service_Sigfox_GetStatus());

		qCR_WaitUntil( (WSSFM1XRX_OK_RESPONSE == ( ret = WSSFM1XRX_AskFrequencyUL(&SigfoxModule, WAIT, &Frequency) ) ) ||
				ret == WSSFM1XRX_FAILURE);
		if(ret == WSSFM1XRX_FAILURE){
			WSSFM1XRX_ResetModule(&SigfoxModule,WSSFM1XRX_Wait_Block);
			qCR_Restart;
		}
		/* Change to frequency specific*/
		Service_Sigfox_SetStatus(WSSFM1XRX_STATUS_CHANGE_FREQ_UL);
		Service_SigfoxDebugDecimal(_VERBOSE_,obj.FreqInFlash); /*Frquency in flash*/
		obj.FreqInFlash = ( (obj.FreqInFlash != 0) && (obj.FreqInFlash < MAX_NUMBER_SIGFOX_FREQUENCY ) ) ? obj.FreqInFlash : SigfoxModule.Frequency;   /*flash arranca en 0 o 0xff al estar vacio*/

		Service_SigfoxDebugDecimal(_VERBOSE_,Frequency);

		if( (request.Request == REQUEST_CHANGE_FREQUENCY && Frequency != request.Frequency ) || (Frequency != obj.FreqInFlash) ){ /*el != es para la primera vez*/

			/*si no es necesario no escribe , si la primera vez esta en la zona que es la flash esta limpia*/
			RCZ = request.Request == REQUEST_CHANGE_FREQUENCY ? request.Frequency:obj.FreqInFlash;
			Service_SigfoxDebugDecimal(_VERBOSE_,RCZ);  /*Freq to write in module*/
			qCR_WaitUntil( (WSSFM1XRX_OK_RESPONSE == (ret = WSSFM1XRX_ChangeFrequencyUL(&SigfoxModule,WAIT,RCZ) )) || ( WSSFM1XRX_MAX_RETRIES_REACHED == ret) );
			if(WSSFM1XRX_MAX_RETRIES_REACHED  == ret ){
				WSSFM1XRX_ResetModule(&SigfoxModule,WSSFM1XRX_Wait_Block);
				qCR_Restart;
			}

			/* Change to frequency DOWLINK*/

			Service_SigfoxDebugDecimal(_VERBOSE_,Service_Sigfox_GetStatus());

			qCR_WaitUntil(( WSSFM1XRX_OK_RESPONSE == (ret = WSSFM1XRX_ChangeFrequencyDL(&SigfoxModule,WAIT,RCZ)) )  || ( WSSFM1XRX_MAX_RETRIES_REACHED == ret) );
			if(WSSFM1XRX_MAX_RETRIES_REACHED  == ret ){
				WSSFM1XRX_ResetModule(&SigfoxModule,WSSFM1XRX_Wait_Block);
				qCR_Restart;
			}

		}

		Service_Sigfox_SetStatus(WSSFM1XRX_STATUS_SAVE_PARM);

		Service_SigfoxDebugDecimal(_VERBOSE_,Service_Sigfox_GetStatus());

		qCR_WaitUntil( (WSSFM1XRX_OK_RESPONSE == (ret = WSSFM1XRX_SaveParameters(&SigfoxModule,WAIT)) ) || ( WSSFM1XRX_MAX_RETRIES_REACHED == ret));
		if(WSSFM1XRX_MAX_RETRIES_REACHED  == ret ){
			WSSFM1XRX_ResetModule(&SigfoxModule,WSSFM1XRX_Wait_Block);
			qCR_Restart;
		}

		Service_Sigfox_SetStatus(WSSFM1XRX_STATUS_GET_ID);
		Service_SigfoxDebugDecimal(_VERBOSE_,Service_Sigfox_GetStatus());
		qCR_WaitUntil( (WSSFM1XRX_OK_RESPONSE == (ret = WSSFM1XRX_GetID(&SigfoxModule,WAIT,SigFoxData.ID))) ||  ( WSSFM1XRX_FAILURE == ret));
		if(WSSFM1XRX_FAILURE  == ret ){
			WSSFM1XRX_ResetModule(&SigfoxModule,WSSFM1XRX_Wait_Block);
			qCR_Restart;
		}
		qDebug_String(Service_Sigfox_GetID());qDebug_Message(" ");

		Service_Sigfox_SetStatus(WSSFM1XRX_STATUS_GET_PAC);
		Service_SigfoxDebugDecimal(_VERBOSE_,Service_Sigfox_GetStatus());

		qCR_WaitUntil( (WSSFM1XRX_OK_RESPONSE == (ret = WSSFM1XRX_GetPAC(&SigfoxModule,WAIT,SigFoxData.PAC)) ) || ( WSSFM1XRX_FAILURE == ret) );
		if(WSSFM1XRX_FAILURE  == ret ){
			WSSFM1XRX_ResetModule(&SigfoxModule,WSSFM1XRX_Wait_Block);
			qCR_Restart;
		}
		qDebug_String(Service_Sigfox_GetPAC());
		qDebug_Message("=========================================");
		Service_Sigfox_SetStatus(WSSFM1XRX_STATUS_MODULE_INITIALIZED);

		Service_SigfoxDebugDecimal(_VERBOSE_,Service_Sigfox_GetStatus());
		SigFoxData.ReadyToUplink = 1;
		qDebug_Message("WSSFM1XRX_MODULE_INITIALIZED");

		if(request.Request == REQUEST_CHANGE_FREQUENCY ) {
			qDebug_Message("qTaskSendNotification");
			if(obj.PtrToTaskFSM != NULL)
				qTask_Notification_Send(obj.PtrToTaskFSM, (void*)OPERATION_SLEEP);
		}
		qTask_Set_State(qTask_Self(),qDisabled);
		request.Request = 0xff;  /*limpiar request*/
		qCR_Yield;
	}qCR_End;

}


void Service_SigfoxDebugDecimal(uint8_t print , uint16_t ValuePrint){
	if (print == 1)
		qDebug_Decimal(ValuePrint);

}
