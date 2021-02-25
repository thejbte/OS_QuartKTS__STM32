/*
 * App.h
 *
 *  Created on: 10/09/2020
 *      Author: Julian
 */

#ifndef SOURCE_APP_APP_H_
#define SOURCE_APP_APP_H_

#include "QuarkTS.h"
#include "qcoroutine.h"
#include <bsp_remapping.h>
#include <data_cofigurator.h>
#include <data_uplink.h>
#include "AT_commands.h"
#include <Task_Service_Sigfox.h>


#define APP_CONFIG_BUILD_VER      				"0.0.0"  /*!< iButton Animal build version */
//#define APP_CAPTION     						"iButton "  APP_CONFIG_BUILD_VER
#define AUT_STRING  							"[Esp.Ing.Julian Bustamante]"
#define INF_STRING  							 QUARKTS_CAPTION "\r\n" \
												 WSSFM1XRX_CAPTION "\r\n" SERVICE_SIGFOX_CAPTION "\r\n"\
												 SHT30_CAPTION "\r\n"



typedef enum {
	APP_ID_DEVICE_WSQ = 0, 				/*wifi */
	APP_ID_DEVICE_GSQ 					/*gps */
}App_idDevice_t;


#define APP_SAMPLES_ADC				10
#define APP_CONFIG_TIME_FSM 		0.01

#define APP_CONFIG_CHECK_FORACTIVE_SENSORS()			AppData_Config.adc1.IsActive\
												|| 	AppData_Config.adc2.IsActive\
												||  AppData_Config.accelerometer.IsActive\
												||  AppData_Config.airquality.IsActive\
												||  (AppData_Config.DI_1 != APPDATACFG_DI_DISABLE)\
												||  (AppData_Config.DI_2 != APPDATACFG_DI_DISABLE)\
												|| 	AppData_Config.temperature.IsActive\
												|| 	AppData_Config.humidity.IsActive
												/*|| 	AppData_Config.GPS_LocIsActive\
												|| 	AppData_Config.WIFI_LocIsActive\*/

#define APP_ANY_STATE_GPS() 						(Service_Gps_GetState() == Service_Gps_State_Done)\
												||	(Service_Gps_GetState() == Service_Gps_State_NotFix)\
												||	(Service_Gps_GetState() == Service_Gps_State_FixNotSamples)\
												||	(Service_Gps_GetState() == Service_Gps_State_Failure)\
												||	(Service_Gps_GetState() == Service_Gps_State_NotEngage)



#define APP_POS_FLASH_COUNT_KEEP_ALIVE	4   /*for write individually*/
#define APP_POS_FLASH_ID_DEVICE			8   /*for write individually*/
#define APP_POS_FLASH_LATITUDE_STORE			12  /* latitude in flash*/
#define APP_POS_FLASH_LONGITUDE_STORE			16  /*longitude in flash*/

//----------------------Downlink-------------------
// 0          1            2                                3                                 4                 5           6       7
//0x00 0x 000  000  00 0  000  0000   DI2,DI1,DO_CTRL,ADC2,ADC1,TH,ONLYLOC, ALWAYSREPORT ,REDUNDANCIA           h            m        s
//ctrl    Cev1 Cev2 Cev3 Cev4 Numev

#define APP_DL_CTRLREGEVENT				0
#define APP_DL_COLOR_1_2_3				1
#define APP_DL_COLOR_3_C_NEVENT			2
#define APP_DL_BITFIELD_SENSORS_1		3 /* DI,DO_CTRL,ADC2,ADC1,TH,ONLYLOC, ALWAYSREPORT ,REDUNDANCIA */  /*APPDATACFG_DI_DISABLE = 0,APPDATACFG_DI_RISING =1*/
#define APP_DL_BITFIELD_SENSORS_2		4
#define APP_DL_TR_HOUR  				5  /*hour min*/
#define APP_DL_TR_MIN  				    6  /*hour min*/
#define APP_DL_TR_SEC  				    7  /*hour min*/

#define APP_DL_BF_CEV1          5
#define APP_DL_BF_CEV2          2
#define APP_DL_BF_CEV3          7
#define APP_DL_BF_CEVC          4

#define APP_DL_BF_DI2           7
#define APP_DL_BF_DI1           6
#define APP_DL_BF_DO_CTRL       5
#define APP_DL_BF_ADC2          4
#define APP_DL_BF_ADC1          3
#define APP_DL_BF_TH            2
#define APP_DL_BF_ONLYLOC       1
#define APP_DL_BF_ALWAYSREPORT  0
#define APP_DL_BF_REDUNDANCIA   7


#define APP_DEFAULT_COLOR_EVENT_1                       1  /*default*/
#define APP_DEFAULT_COLOR_EVENT_2                       2  /*default*/
#define APP_DEFAULT_COLOR_EVENT_3                       3  /*default*/
#define APP_DEFAULT_COLOR_EVENT_C                       4  /*default*/



extern qTask_t TaskApplicationFSM;
extern qSM_t   ApplicationFSM;
extern qTask_t TaskHandlerEvents_Scan;





extern uint32_t	CounterKeepAlive ;
extern BSP_WakeUp_Source_t WakeUp_Source;



//extern AppDataCfg_all_t AppData_Config;

/**
 * @brief Scan sensore and handler events
 * */
void App_Task_ScanAndEvents_Callback(qEvent_t arg);

qSM_Status_t App_State_CheckConditions(qSM_Handler_t fsm);
qSM_Status_t App_State_ConfigMode(qSM_Handler_t fsm);
qSM_Status_t App_State_Mode(qSM_Handler_t fsm);
qSM_Status_t App_State_NotificationWait(qSM_Handler_t fsm);
qSM_Status_t App_State_PushButtonWait(qSM_Handler_t fsm);
qSM_Status_t App_State_Sleep(qSM_Handler_t fsm);
void App_State_Failure(qSM_Handler_t fsm);
void App_Task_Idle(qEvent_t e);
uint8_t App_DiscrimateFrameDownlink(uint8_t *NumericFrame);
void App_Update_BattSocOrmV(void);

#endif /* SOURCE_APP_APP_H_ */
