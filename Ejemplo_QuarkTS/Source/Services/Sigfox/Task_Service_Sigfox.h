/*!
 * *******************************************************************************
 * @file Task_Service_Sigfox.h
 * @author Esp.Ing.Julian Bustamante N
 * @version 1.2.5
 * @date Jan  7, 2021
 * @brief Sigfox service interface for the sigfox module
 *********************************************************************************/


#ifndef INC_TASK_TASK_SERVICE_SIGFOX_H_
#define INC_TASK_TASK_SERVICE_SIGFOX_H_

/*define struct data frame in your app.h*/

#include "QuarkTS.h"
#include "wssfm1xrx.h"

#define SERVICE_SIGFOX_VERSION    "1.2.5"
#define SERVICE_SIGFOX_CAPTION     "SigFox_Service " SERVICE_SIGFOX_VERSION

#define _VERBOSE_	0			/*!< 0 or 1 for print debug sequence*/



#define WAIT WSSFM1XRX_Wait_NonBlock
#define	MAX_SIZE_IBUTTON_DATA	12

#define MAX_NUM_REPETICIONES 1  /*usar para queue size elements*/
#define MAX_NUM_ELEMENT_ENQUEUE 10

#define MAX_NUMBER_SIGFOX_FREQUENCY 6



typedef enum{
	OPERATION_SLEEP =8
}NotifyApp;

typedef struct{
	char ID[MAX_SIZE_IBUTTON_DATA];
	char PAC[22];
	uint16_t VBatt;
	WSSFM1XRX_Service_Status_t WilsolService_Status;
	uint8_t ReadyToUplink;
}SigFox_Info_t;


/**
 * @brief Structure with request flag and union for shared memory
 */
typedef struct {
	union{
		uint8_t Payload[MAX_SIZE_IBUTTON_DATA];
		WSSFM1XRX_FreqUL_t Frequency;
	};
	uint8_t Request;
	uint8_t Repeticiones;
	uint8_t Source;
}Service_SigfoxRequest_t;

typedef enum{
	REQUEST_SEND_PAYLOAD = 0,
	REQUEST_SEND_PAYLOAD_DOWNLINK,
	REQUEST_CHANGE_FREQUENCY,
	REQUEST_GET_BATTERY
}Request_Service_t;



/**
 * @brief This function run  sigfox service
 * @param enable: turn on or turn off service
 * */
void Service_Sigfox_Run(uint8_t enable);

/**
 * @brief This function receive incoming frame to SigFox module
 * */
void Service_Sigfox_ISRHandler(const char rxchar);


/**
 * @brief This function Configure task and queue SigFox service
 * */
void Service_Sigfox_Setup(WSSFM1XRX_FreqUL_t DefaultConfigRC , DigitalFcn_t Reset, DigitalFcn_t WkUp , TxFnc_t SigfoxPutc , TickReadFcn_t GetTick);
/**
 * @brief This function Initialize SigFox service
 * @param PtrToTaskFSM pointer to task FSM where controller service
 * @param FreqInFlash Data read from microcontroller flash
 * */
void Service_Sigfox_Init(qTask_t *PtrToTaskFSM , uint16_t FreqInFlash, uint8_t Enable,uint8_t repeat);

/**
 * @brief This function Get Actual state of SigFox service
 * @return  Actual state
 * */
WSSFM1XRX_Service_Status_t Service_Sigfox_GetStatus(void);


/**
 * @brief This function Clear Actual state of SigFox service
 * */
void Service_Sigfox_ResetStatus(void);

/**
 * @brief This function Get battery from sigfox module
 * @return  battery in mv
 * * */
uint16_t Service_Sigfox_GetBattery(void);

/**
 * @brief This function Get ID from sigfox module
 * @return  pointer to char -> string ID
 * * */
char* Service_Sigfox_GetID(void);

/**
 * @brief This function Get PAC from sigfox module
 * @return  pointer to char -> string PAC
 * * */
char* Service_Sigfox_GetPAC(void);

/**
 * @brief This function get frequency from sigfox module
 * @return WSSFM1XRX_FreqUL_t enum frequency
 * @note if module yet not being initialized this return
 *       frequency stored in microcontroller flash or freq default
 * */
WSSFM1XRX_FreqUL_t Service_Sigfox_GetFreqUpLink(void);

/**
 * @brief This function get frame transmitted
 * @param pointer to string frame
 * @note: Only used after send message
 * * */
char* Service_Sigfox_GetFrameSend();

/**
 * @brief This function Get flag ready to uplink initialized
 * @return  int 0 or 1
 * * */
int Service_Sigfox_GetReadyToUpLink(void);

/**
 * @brief This function clear flag ready to uplink
 * * */
void Service_Sigfox_ClearReadyToUpLink(void);

/**
 * @brief This function send message - enqueue message
 * * */
//void Service_Sigfox_Send( Service_SigfoxRequest_t *Service_SigfoxRequest);
void Service_Sigfox_Send( uint8_t *data, uint8_t downlink);



/**
 * @brief Wake up hardware sigfox
 * */
WSSFM1XRX_Return_t Service_Sigfox_WakeUp(void);

/**
 * @brief sleep hardware sigfox
 * */
WSSFM1XRX_Return_t Service_Sigfox_Sleep(void);

/**
 * @brief reset hardware sigfox
 * */
WSSFM1XRX_Return_t Service_Sigfox_Reset(void);


/**
 * @brief Get frame downlink after send uplink message.
 * */
uint8_t* Service_Sigfox_GetDownlinkFrame(void);

/**
 * @brief Discriminate frame incoming from sigfox
 * */
WSSFM1XRX_DL_Return_t Service_Sigfox_DownlDiscriminate(void);

/**
 * @brief Returns the empty status of the Queue
 * */
uint8_t Service_Sigfox_QueueIsEmpty(void);

/**
 * @brief API function for change frequency
 * @param Freq: frquency uplink ( WSSFM1XRX_RCZ4 or WSSFM1XRX_RCZ2)
 * */
void Service_Sigfox_ChangeFrequency(WSSFM1XRX_FreqUL_t Freq);

/**
 * @brief This function run service in backgroud
 * @param evendata
 * */
void Service_Sigfox_Callback(qEvent_t e) ;

/**
 * @brief This callback is Dispatcher Payload
 * @param evendata
 * */
void Service_Sigfox_UplinkDispatcher_Callback(qEvent_t e) ;

/**
 * @brief print debug message
 * @param print: transmit if true  ( value is true or false)
 * */
void Service_SigfoxDebugDecimal(uint8_t print , uint16_t ValuePrint);


/** @brief get status of the downlink
 * @return 1 if downlink incomming is ok or 0 if failure*/
uint8_t Service_Sigfox_GetDownlinkStatus(void);


#endif /* INC_TASK_TASK_SERVICE_SIGFOX_H_ */
