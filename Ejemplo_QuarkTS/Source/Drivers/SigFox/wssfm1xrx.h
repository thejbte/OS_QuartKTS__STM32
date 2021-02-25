/*!
 * *******************************************************************************
 * @file WSSFM1XRX.h
 * @author julian bustamante
 * @version 1.5.6
 * @date Nov 18 , 2020
 * @brief Sigfox interface for the sigfox module. Interface
 * specific for module wisol SFM11R2D.
 *********************************************************************************/

#ifndef SOURCES_WSSFM1XRX_H_
#define SOURCES_WSSFM1XRX_H_

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define WSSFM1XRX_VERSION    	"1.5.6"
#define WSSFM1XRX_CAPTION     	"WSSFM1XRX " WSSFM1XRX_VERSION

/*BOOL VALUES*/
#ifndef SF_TRUE
	#define SF_TRUE						( 1 )
#endif
#ifndef SF_FALSE
	#define SF_FALSE 					( 0 )
#endif

/*Down link definitions ---------------------------------------------------------*/
/** Each byte represented in hex */
#define WSSFM1XRX_DL_BYTE_SIZE 			( 2 )

#define WSSFM1XRX_DL_PAYLOAD_SYZE 		( 8 )

/** Header(3) + Payload(16) + Spaces(7) */
#define WSSFM1XRX_DL_PAYLOAD_LENGTH 	( 26u )

/** Offset between bytes within the string frame */
#define WSSFM1XRX_DL_BYTES_OFFSET 		( 3 )

/** Minimum report time --> 10.285 min*/
#define WSSFM1XRX_DL_MIN_REPORT_TIME 	( 617 )

/** Downlink request period maximun*/
#define WSSFM1XRX_DL_REQ_PERIOD_TRANSMISSION_MAX_DAY 	( 4 )

/** Downlink request period horas */
#define WSSFM1XRX_DL_REQ_PERIOD_H 		( 6 )

/** Downlink request period horas --> cada 6 horas*/
#define WSSFM1XRX_DL_REQ_PERIOD_S  		( WSSFM1XRX_DL_REQ_PERIOD_H*3600 ) /* 360 21600*/

/** X time base in seconds for wakeup */
#define WSSFM1XRX_DL_TIMEREQUEST(X)		(uint8_t)( (WSSFM1XRX_DL_REQ_PERIOD_S)/(X) )

#define WSSFM1XRX_DL_IF_ANY_ERROR(x)	(( (x) == (WSSFM1XRX_DL_HEAD_ERROR) ) || ( (x) == (WSSFM1XRX_DL_TAIL_ERROR) ) || ( (x) == (WSSFM1XRX_DL_LENGTH_ERROR) ) )


/* Frame types -------------------------------------------------------------------*/
#define WSSFM1XRX_DL_FRAME_REPORT_TIME  ( 5 )
#define WSSFM1XRX_DL_FRAME_REPORT_TIME_AND_TURN_OFF_MOTO  ( 5 )

/* Numeric frame offsets ---------------------------------------------------------*/
#define WSSFM1XRX_DL_CTRLREG 	( 0 )
#define WSSFM1XRX_DL_TREP 		( 2 )
#define WSSFM1XRX_DL_P_ON_OFF   ( 4 ) /*turn on off */


/*length buffer to transmition*/
#define WSSFM1XRX_BUFF_TX_FRAME_LENGTH 	( 37 )

/*length buffer to reception*/
#define WSSFM1XRX_BUFF_RX_FRAME_LENGTH 	( 45 )

/*Delays for expected response WISOL module------------------------------------------------*/
/** Downlink frame timeout */
#define WSSFM1XRX_DL_TIMEOUT 						( 60000 ) /*60s*/

/*Delay Time for WSSFM1XRX_SendMessage WISOL module [ms]*/
#define WSSFM1XRX_SEND_MESSAGE_TIME_DELAY_RESP	    ( 6000 ) /*6000 6s*/

/*GENERAL DELAY TIME FOR COMMANDS [ms]*/
#define WSSFM1XRX_GENERAL_TIME_DELAY_RESP			( 4000 )/*with 4000 ms timeout before receiving */

/*Delay Time for WSSFM1XRX_WakeUP WISOL module [ms]*/
#define WSSFM1XRX_WAKEUP_TIME_DELAY_PULSE			( 200 )

/*Delay Time for waiting WSSFM1XRX_WakeUP WISOL module start [ms]*/
#define WSSFM1XRX_WAKEUP_WAIT_TIME_DELAY_RESP		( 300 )

/*Delay Time for WSSFM1XRX_SLEEP WISOL module [ms]*/
#define WSSFM1XRX_SLEEP_TIME_DELAY_RESP	    		( 500 ) /*500*/

#define WSSFM1XRX_SLEEP_TIME_RESET	       			( 1000 )

/*GENERAL DELAY TIME FOR COMMANDS [ms]*/
#define WSSFM1XRX_SEND_RAW_MESSAGE_TIME_DELAY_RESP	( 1000 )

/*For Strtol*/
#define BASE_DECIMAL 		( 10 )

/**Char no print*/
#define CHAR_PRINT_BELOW	( 10 )

/**Char no print*/
#define CHAR_PRINT_ABOVE	( 122 )
/**
 * @brief Pointer to Function type TickReadFcn_t : function Get Tick in ms.
 * 
 *@note In the default implementation, this variable "tick" is incremented each 1ms
 *       in ISR.
 * Example :
 * 	    uint32_t ReadTick_ms(void){
 *			tick++;	}
 * @param none.
 * @return uint32_t.
 */
typedef uint32_t (*TickReadFcn_t)(void); /*TODO : namespaces should be object-consistent*/


/**
 * @brief Pointer to Function type DigitalFcn_t : enable or disable pin reset.
 * @note Example :
 * 	    void RSTCtrl_Sigfox(uint8_t sValue){
 *		     if(sValue) HAL_GPIO_WritePin(GPIOA, RST_SIGFOX_Pin, GPIO_PIN_SET);
 *		     else HAL_GPIO_WritePin(GPIOA, RST_SIGFOX_Pin, GPIO_PIN_RESET); 
 *		}
 * @param uint8_t.
 * @return none.
 */
typedef void (*DigitalFcn_t)(uint8_t); /*TODO : namespaces should be object-consistent*/


/**
 * @brief Pointer to Function type TxFnc_t : Transmission by UART.
 * @note Example :
 *  	void UART_SIGFOX_TX_STM(void * Sp, char c){
 *  		HAL_UART_Transmit(&huart1,(uint8_t*)&c,USART_TX_AMOUNT_BYTES,USART_TIMEOUT);
 *		}
 * @param void *
 * @param char
 * @return none.
 */
typedef void (*TxFnc_t)(void*,char); /*TODO : namespaces should be object-consistent*/


/**
 * @brief Pointer to Function type RxFnc_t : Reception  by UART.
 * @note Example :
 *		unsigned char UART_SIGFOX_RX_STM( unsigned char * Chr){
 *			*Chr = UART_RX.Data;
 *			return WRAPER_ERR_OK;
 *		}
 * @param unsigned char*
 * @return unsigned char.
 */
typedef unsigned char (*RxFnc_t)(unsigned char*); /*TODO : namespaces should be object-consistent*/


/**
 * @brief Return codes for downlink operation.
 */
typedef enum{
	WSSFM1XRX_DL_SUCCESS,      /* Downlink successfully processed */
	WSSFM1XRX_DL_HEAD_ERROR,   /* Could not find RX */
	WSSFM1XRX_DL_TAIL_ERROR,   /* Could not find \r */
	WSSFM1XRX_DL_LENGTH_ERROR, /* Wrong length */
	WSSFM1XRX_DL_TIME_OK,		/*Time success*/
	WSSFM1XRX_DL_UNKNOWN,
	WSSFM1XRX_DL_DISCRIMINATE_ERROR
}WSSFM1XRX_DL_Return_t;

/**Frequency  Hz - Uplink********************************************************/
typedef enum{
	WSSFM1XRX_RCZ1 = 0,
	WSSFM1XRX_RCZ2,
	WSSFM1XRX_RCZ3,
	WSSFM1XRX_RCZ4,
	WSSFM1XRX_RCZ5,
	WSSFM1XRX_RCZ6,
}WSSFM1XRX_FreqUL_t;


/** @brief enum flag blobking or non blocking for function of  wait*/
typedef enum{
	WSSFM1XRX_FNonBlock = 0,
	WSSFM1XRX_FBlock 
}WSSFM1XRX_FlagBlock_t;

/** @brief enum status state wisol internal */
typedef enum{
	WSSFM1XRX_IDLE=0,
	WSSFM1XRX_RUNNING,
	WSSFM1XRX_W_IDLE,
	WSSFM1XRX_W_RUNNING
}WSSFM1XRX_ApiState_t;

/** @brief enum status functions for user******************************************************
 * */
typedef enum{
	WSSFM1XRX_STATUS_SLEEP = 0,
	WSSFM1XRX_STATUS_WKUP,
	WSSFM1XRX_STATUS_CHK_MODULE ,
	WSSFM1XRX_STATUS_GET_VOLTAGE,
	WSSFM1XRX_STATUS_ASK_FREQ_UL,
	WSSFM1XRX_STATUS_CHANGE_FREQ_UL ,
	WSSFM1XRX_STATUS_SAVE_PARM ,
	WSSFM1XRX_STATUS_GET_ID,
	WSSFM1XRX_STATUS_GET_PAC,
	WSSFM1XRX_STATUS_MODULE_INITIALIZED,
	WSSFM1XRX_STATUS_CHK_CHANNELS ,
	WSSFM1XRX_STATUS_RST_CHANNELS ,
	WSSFM1XRX_STATUS_SEND_MESSAGE , /*ENVIAR*/
	WSSFM1XRX_STATUS_SENT_MESSAGE , /*ENVIADO*/
	WSSFM1XRX_STATUS_IDLE,

	WSSFM1XRX_STATUS_MODULE_NOT_INITIALIZED,
	WSSFM1XRX_STATUS_IDLE_FOR_SEND_MESSAGE

}WSSFM1XRX_Service_Status_t;

/**Struct for store macro channnels sigfox module*/
typedef struct{
	uint8_t x;
	uint8_t y;
}WSSFM1XRX_Channels_t;
/**
 * @brief Return codes for TIME and Expected Response operation.
 */
typedef enum{
	WSSFM1XRX_TIMEOUT   = 0,
	WSSFM1XRX_WAITING,
	WSSFM1XRX_RSP_NOMATCH,
	WSSFM1XRX_OK_RESPONSE,
	WSSFM1XRX_NONE,
	WSSFM1XRX_INIT_OK,
	WSSFM1XRX_PROCESS_FAILED, 		
	WSSFM1XRX_CHANN_OK, 			
	WSSFM1XRX_CHANN_NO_OK, 		
	WSSFM1XRX_DEFAULT,
	WSSFM1XRX_FAILURE,
	WSSFM1XRX_MAX_RETRIES_REACHED
}WSSFM1XRX_Return_t;

typedef uint8_t Private_t; /* why?? */
/*Struct  containing all data*/
typedef struct WSSFM1XRXConfig{
	DigitalFcn_t RST;
	DigitalFcn_t WKUP;
	TxFnc_t TX_WSSFM1XRX;
	TickReadFcn_t TICK_READ;
	/*Decodificar trama numerica return*/
	/* WSSFM1XRX_DL_Return_t (*CallbackDownlink)(struct WSSFM1XRXConfig* );*/
	char *RxFrame; /*volatile char *RxFrame*/
	uint8_t SizeBuffRx;
	volatile unsigned char RxReady;
	volatile uint8_t RxIndex;
	uint8_t StatusFlag;
	WSSFM1XRX_FreqUL_t Frequency;
	Private_t DownLink; /*!< No use*/
	uint32_t UL_ReportTimeS;
	uint8_t DL_NumericFrame[WSSFM1XRX_DL_PAYLOAD_SYZE];
	WSSFM1XRX_ApiState_t State_W;
	WSSFM1XRX_ApiState_t State_Api;
	uint8_t NumberRetries;
	uint8_t MaxNumberRetries;
}WSSFM1XRXConfig_t;

/*Deprecated*/
/*typedef WSSFM1XRX_DL_Return_t (*WSSFM1XRX_Callback_t)(WSSFM1XRXConfig_t*);*/


/**
 * @brief  Pointer to function type WSSFM1XRX_WaitMode_t
 * @param obj Structure containing all data from the Wisol module.	
 * @param msec time to wait in mili second.
 * @return WSSFM1XRX_Return_t 
 */
typedef WSSFM1XRX_Return_t (*WSSFM1XRX_WaitMode_t)(WSSFM1XRXConfig_t* ,uint32_t);

/*================================================================================
 *   prototypes
 *================================================================================*/



/**
 * @brief Function initialize the Wisol module.
 * @param obj Structure containing all data from the Wisol module.
 * @param ...
 * @return Operation result in the form WSSFM1XRX_Return_t.
 */
WSSFM1XRX_Return_t WSSFM1XRX_Init(WSSFM1XRXConfig_t *obj, DigitalFcn_t Reset, DigitalFcn_t WkUp, TxFnc_t Tx_Wssfm1xrx,WSSFM1XRX_FreqUL_t Frequency_Tx ,TickReadFcn_t TickRead,char* Input , uint8_t SizeInput, uint8_t MaxNumberRetries);
/**
 * @brief Function delay non blocking.
 * @note  the function GetTick_ms must be initialized to work
 * @param obj Structure containing all data from the Wisol module.	
 * @param msec time to wait in mili second.
 * @return Operation result in the form WSSFM1XRX_Return_t:
 */
WSSFM1XRX_Return_t WSSFM1XRX_Wait_NonBlock(WSSFM1XRXConfig_t *obj, uint32_t msec);

/**
 * @brief Function delay blocking.
 * @note  the function GetTick_ms must be initialized to work
 * @param obj Structure containing all data from the Wisol module.	
 * @param msec time to wait in mili second.
 * @return Operation result in the form WSSFM1XRX_Return_t:
 */
WSSFM1XRX_Return_t WSSFM1XRX_Wait_Block(WSSFM1XRXConfig_t *obj , uint32_t msec);

/**
 * @brief Function set low power the Wisol module.
 * @param obj Structure containing all data from the Wisol module.
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @return Operation result in the form WSSFM1XRX_Return_t.
 */
WSSFM1XRX_Return_t WSSFM1XRX_Sleep(WSSFM1XRXConfig_t *obj ,WSSFM1XRX_WaitMode_t Wait );

/**
 * @brief Function wakeup from pin extern the Wisol module.
 * @param obj Structure containing all data from the Wisol module.
 * @param Wait Pointer to function delay blocking of type WSSFM1XRX_WaitMode_t
 * @return Operation result in the form WSSFM1XRX_Return_t.
 */
WSSFM1XRX_Return_t WSSFM1XRX_WakeUP(WSSFM1XRXConfig_t *obj );

/**
 * @brief Function reset the Wisol module.
 * @param obj Structure containing all data from the Wisol module.
 * @param Wait Pointer to function delay blocking, of type WSSFM1XRX_WaitMode_t
 * @return Operation result in the form WSSFM1XRX_Return_t.
 */
WSSFM1XRX_Return_t WSSFM1XRX_ResetModule(WSSFM1XRXConfig_t *obj ,WSSFM1XRX_WaitMode_t Wait  );

/**
 * @brief Function check module sending AT command to the Wisol module.
 * @param obj Structure containing all data from the Sigfox module.
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @return Operation result in the form WSSFM1XRX_Return_t.
 */
WSSFM1XRX_Return_t WSSFM1XRX_CheckModule(WSSFM1XRXConfig_t *obj, WSSFM1XRX_WaitMode_t Wait);

/**
 * @brief Function get ID unique from Wisol module.
 * @param obj Structure containing all data from the Sigfox module.
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @param IDStr Buffer for copy string ID
 * @return Operation result in the form WSSFM1XRX_Return_t
 */
WSSFM1XRX_Return_t WSSFM1XRX_GetID(WSSFM1XRXConfig_t *obj, WSSFM1XRX_WaitMode_t Wait ,char *IDStr);

/**
 * @brief Function get PAC unique from Wisol module.
 * @param obj Structure containing all data from the Sigfox module.
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @param PACStr Buffer for copy string PAC
 * @return Operation result in the form WSSFM1XRX_Return_t
 */
WSSFM1XRX_Return_t WSSFM1XRX_GetPAC(WSSFM1XRXConfig_t *obj, WSSFM1XRX_WaitMode_t Wait , char *PACStr);

/**
 * @brief Function get supply Voltage  from Wisol module.
 * @param obj Structure containing all data from the Sigfox module.
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @param mVolt pointer to variable for store mili voltage
 * @return Operation result in the form WSSFM1XRX_Return_t
 */
WSSFM1XRX_Return_t WSSFM1XRX_GetVoltage(WSSFM1XRXConfig_t *obj, WSSFM1XRX_WaitMode_t Wait ,uint16_t * mVolt);

/**
 * @brief Function Send command to the Wisol module.
 * @param obj Structure containing all data from the Sigfox module.
 * @param Payload containing string to transmitions at Wisol module.
 * @param ExpectedResponse expectedResponse expected Response from module Wisol .
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @param msec time to wait in mili second.
 * @return Operation result in the form WSSFM1XRX_Return_t
 */
WSSFM1XRX_Return_t WSSFM1XRX_SendRawMessage(WSSFM1XRXConfig_t *obj,char* Payload,char* ExpectedResponse,char * BuffStr,WSSFM1XRX_WaitMode_t Wait,uint32_t msec);

/**
 * @brief Function ask channels of the transceiver.
 * @param obj Structure containing all data from the Sigfox module.
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @return Operation result in the form WSSFM1XRX_Return_t
 */
WSSFM1XRX_Return_t WSSFM1XRX_AskChannels(WSSFM1XRXConfig_t *obj,WSSFM1XRX_WaitMode_t Wait, WSSFM1XRX_Channels_t *Channels );

/**  Revisar DOC--------
 * @brief Function verificate channels of the transceiver.
 * @param obj Structure containing all data from the Sigfox module.
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @return Operation result in the form WSSFM1XRX_Return_t.
 */
WSSFM1XRX_Return_t WSSFM1XRX_CheckChannels(WSSFM1XRXConfig_t *obj,WSSFM1XRX_WaitMode_t Wait );

/**
 * @brief Function reset channels from Wisol module.
 * @param obj Structure containing all data from the Sigfox module.
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @return Operation result in the form WSSFM1XRX_Return_t
 */
WSSFM1XRX_Return_t WSSFM1XRX_ResetChannels(WSSFM1XRXConfig_t *obj,WSSFM1XRX_WaitMode_t Wait );

/**
 * @brief Function change frequency uplink from Sigfox module.
 * @param obj Structure containing all data from the Wisol module.
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @param Frequency frequency trasmission type WSSFM1XRX_FreqUL_t
 * @return Operation result in the form WSSFM1XRX_Return_t
 */
WSSFM1XRX_Return_t WSSFM1XRX_ChangeFrequencyUL(WSSFM1XRXConfig_t *obj,WSSFM1XRX_WaitMode_t Wait ,WSSFM1XRX_FreqUL_t Frequency);

/**
 * @brief Function change frequency Downlink from Sigfox module.
 * @param obj Structure containing all data from the Wisol module.
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @param Frequency frequency receive type WSSFM1XRX_FreqUL_t
 * @return Operation result in the form WSSFM1XRX_Return_t
 */
WSSFM1XRX_Return_t WSSFM1XRX_ChangeFrequencyDL(WSSFM1XRXConfig_t *obj,WSSFM1XRX_WaitMode_t Wait , WSSFM1XRX_FreqUL_t Frequency);

/**
 * @brief Function ask frequency uplink from Wisol module.
 * @param obj Structure containing all data from the Sigfox module.
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @param Frequency pointer to variable for store Frequency
 * @return Operation result in the form WSSFM1XRX_Return_t
 * */
WSSFM1XRX_Return_t WSSFM1XRX_AskFrequencyUL(WSSFM1XRXConfig_t *obj,WSSFM1XRX_WaitMode_t Wait, WSSFM1XRX_FreqUL_t *Frequency );
/**
 * @brief Function save parameter in the flash memory from Sigfox module.
 * @param obj Structure containing all data from the Wisol module.
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @return Operation result in the form WSSFM1XRX_Return_t
 */
WSSFM1XRX_Return_t WSSFM1XRX_SaveParameters(WSSFM1XRXConfig_t *obj, WSSFM1XRX_WaitMode_t Wait );

/**
 * @brief Function send message frame in string hexadecimal to sigfox module.
 * @param obj Structure containing all data from the Sigfox module.
 * @param Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @param data Structure containing frame to send the Sigfox module.
 * @param CopyDataTx buffer for trasmission of message, size minimun 37 bytes
 * @param size number of bytes in the payload. less o equal to 12 bytes.
 * @param eDownlink downlink enable o disable (0/1)
 * 
 * @return Operation result in the form WSSFM1XRX_Return_t
 */
WSSFM1XRX_Return_t WSSFM1XRX_SendMessage(WSSFM1XRXConfig_t *obj,WSSFM1XRX_WaitMode_t Wait, void* data,void * CopyDataTx, uint8_t size, uint8_t eDownlink);

/**
 * @brief Function ISR UART receive incoming frame to Sigfox module.
 * the buffer is stored in the structure obj->RxFrame.
 * @param obj Structure containing all data from the Sigfox module.
 * @param RxChar char received by uart
 * @return void.
 */
void WSSFM1XRX_ISRRX(WSSFM1XRXConfig_t *obj, const char RxChar);

/**
 * @brief Function verificate response received from Wisol module.
 * @param obj Structure containing all data from the Sigfox module.
 * @param expectedResponse expected Response from module sigfox .
 * @return Operation result in the form WSSFM1XRX_Return_t.
 */
WSSFM1XRX_Return_t WSSFM1XRX_MatchResponse(WSSFM1XRXConfig_t *obj, char *expectedResponse);
/**
 * @brief Function to discriminate downlink frames.
 * @param obj Structure containing the incoming frame from the Sigfox module.
 * @return Operation result in the form WSSFM1XRX_DL_Return_t.
 */
WSSFM1XRX_DL_Return_t DL_DiscriminateDownLink(WSSFM1XRXConfig_t* obj);


/**
 * @brief function aux send command and wait to sigfox module.
 * @param obj Structure containing all data from the Sigfox module.
 * @param Wait Pointer to function delay blocking or non blocking, of type WSSFM1XRX_WaitMode_t
 * @param CommandStr Pointer to char *  containing Command AT to send the Sigfox module.
 * @param BuffStr Pointer to char *  to store the response of the sigfox module.
 * 
 * @return Operation result in the form WSSFM1XRX_DL_Return_t.
 */
WSSFM1XRX_Return_t WSSFM1XRX_GetRespNoexpected(WSSFM1XRXConfig_t *obj,WSSFM1XRX_WaitMode_t Wait ,char * CommandStr, char * BuffStr);
#endif /* SOURCES_WSSFM1XRX_H_ */
