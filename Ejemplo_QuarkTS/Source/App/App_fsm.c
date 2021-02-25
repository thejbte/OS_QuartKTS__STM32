/*
 * App_fsm.c
 *
 *  Created on: Sep 16, 2020
 *      Author: Julian
 */

#include "App.h"

#define APP_MAX_WAIT_TIME_TO_PRESS_BUTTON 5.0
#define APP_MAX_WAITING_TIME_TO_LED_BLINK	2.0
#define TIMEBLINKLED 0.3
/*	Numero de pulsaciones	*/
#define APP_ONEPRESS	1
#define APP_TWOPRESS	2
#define APP_THREEPRESS	3
#define APP_FOURPRESS	4

#define APP_MAX_NUM_PULSATION 3

static uint8_t Nclick = 0;


static void BlinkColor(Colores_t color , float time);

/*TODO: meter downlink y id pac inicializar*/
extern AppDataCfg_all_t AppData_Config;
/*===========================================================================================*/
qSM_Status_t App_State_CheckConditions(qSM_Handler_t fsm){
	static qSTimer_t TimeoutUsb = QSTIMER_INITIALIZER;
	if(fsm->Signal ==  QSM_SIGNAL_ENTRY){
		qSTimer_Set(&TimeoutUsb, 1.0);  /*wait config usb*/
		qDebug_Message("App_State_CheckConditions");
		BSP_GPIO_DISPLAY_COLOR_RGB( AppData_Config.Pulsation_1.rgb);
	}

	qCR_Begin{
		if(qSTimer_Expired(&TimeoutUsb)){
			if(strlen(AppData_Config.Id_module) < 8 || strlen(AppData_Config.Pac_module) < 16){
				Service_Sigfox_Run(1);
				qCR_WaitUntil(Service_Sigfox_GetStatus() == WSSFM1XRX_STATUS_MODULE_INITIALIZED);
				strncpy(AppData_Config.Pac_module , Service_Sigfox_GetPAC() , 17) ;
				strncpy(AppData_Config.Id_module , Service_Sigfox_GetID() , 9) ;
				BSP_FLASH_WRITE(BSP_FLASH_INIT_ADDR_RESERVED_DATA_CONF, &AppData_Config,sizeof(AppData_Config));
				qTrace();
			}

			if(BSP_USB_STATE_CONFIGURED()){
				fsm->NextState = App_State_ConfigMode;
				return qSM_EXIT_SUCCESS;
			}
			else{

				/*add code*/
				fsm->NextState = App_State_Mode;
			}
		}
	}qCR_End;
	return qSM_EXIT_SUCCESS;
}



/*===========================================================================================*/
qSM_Status_t App_State_Mode(qSM_Handler_t fsm){


	if(fsm->Signal ==  QSM_SIGNAL_ENTRY){
		qDebug_Message("App_State_Mode");
	}


	if(WakeUp_Source.Source == WKUP_PIN){
		fsm->NextState =App_State_PushButtonWait;
	}else if(WakeUp_Source.Source == WKUP_TIME){

		qTask_Set_State(&TaskHandlerEvents_Scan, qEnabled);
		qTask_Set_Data(&TaskHandlerEvents_Scan,(void*)WKUP_TIME);
		fsm->NextState = App_State_NotificationWait;

	}else {
		fsm->NextState = App_State_Sleep;
		return qSM_EXIT_SUCCESS;
	}


	return qSM_EXIT_SUCCESS;
}

/*===========================================================================================*/

qSM_Status_t App_State_NotificationWait(qSM_Handler_t fsm){
	qEvent_t e = fsm->Data;
	if(fsm->Signal ==  QSM_SIGNAL_ENTRY){
		qDebug_Message("App_State_NotificationWait");
	}

	if(e->Trigger == byNotificationSimple && 	( (int)e->EventData == OPERATION_SLEEP) ){ /*check task end*/
		fsm->NextState = App_State_Sleep;
		return qSM_EXIT_SUCCESS;
	}
	return qSM_EXIT_SUCCESS;
}
/*===========================================================================================*/

qSM_Status_t App_State_PushButtonWait(qSM_Handler_t fsm){
	//char *array[] = {"ZEROPRESS","ONEPRESS","TWOPRESS", "THREEPRESS", "FOURPRESS"}; //qDebug_Message(array[Nclick]);

	if(fsm->Signal ==  QSM_SIGNAL_ENTRY){
		qDebug_Message("App_State_PushButtonWait");
	}

	Nclick =BSP_GPIO_DEBOUNCE_GET_CLICK();

	/*iButton Click only*/
	if(AppData_Config.NumPulsation != 0){

	}else{
		/*wifi-gps-sensor*/
		qTask_Set_State(&TaskHandlerEvents_Scan, qEnabled);			/*launch check task*/
		qTask_Set_Data(&TaskHandlerEvents_Scan, (void*)WKUP_PIN);
		fsm->NextState = App_State_NotificationWait;
		return qSM_EXIT_SUCCESS;
	}

	return qSM_EXIT_SUCCESS;
}

/*===========================================================================================*/
qSM_Status_t App_State_ConfigMode(qSM_Handler_t fsm){

	if(fsm->Signal ==  QSM_SIGNAL_ENTRY){
		qDebug_Message("App_State_ConfigMode");
		//BSP_GPIO_DISPLAY_COLOR_RGB( COLOR_RGB_BLUE);
	}
	/*wait config device with atcli*/
	if(BSP_USB_STATE_CONFIGURED()){
		if( qTask_EventFlags_Check(qTask_Self(), QEVENTFLAG_01, 0, 0) ){
			BlinkColor(COLOR_RGB_YELLOW, 0.1);
		}else
			BlinkColor(COLOR_RGB_BLUE, 0.5);
	}
	else{
		BSP_SYSTEM_RESET_SFT(); /*update data*/
	}

	return qSM_EXIT_SUCCESS;
}

/*===========================================================================================*/

qSM_Status_t App_State_Sleep(qSM_Handler_t fsm){
	WSSFM1XRX_Return_t RetSigfox;
	if(fsm->Signal ==  QSM_SIGNAL_ENTRY){
		qDebug_Message("App_State_Sleep");
		Service_Sigfox_WakeUp();
	}

	/*Clear always click and time sametime*/
	BSP_SYSTEM_CLEAR_FLAG_WU();
	BSP_SYSTEM_CLEAR_FLAG_WUT();


	//BSP_FUEL_GAUGE_SLEEP();
	BSP_GPIO_DISABLE_ANALOG();
	BSP_GPIO_DISABLE_SENSORS();


	if( ( (RetSigfox = Service_Sigfox_Sleep()) == WSSFM1XRX_OK_RESPONSE ) || (WSSFM1XRX_MAX_RETRIES_REACHED == RetSigfox  ) ){
		qDebug_Message("-----Core Sleep-----");
		//BSP_FUEL_GAUGE_SLEEP();
		BSP_GPIO_DISPLAY_COLOR_RGB(COLOR_RGB_BLACK);
		BSP_SYSTEM_CORE_SLEEP();
	}
	/*sleep sigfox, gps ,sensor and anythings*/
	return qSM_EXIT_SUCCESS;
}
/*===========================================================================================*/

void App_State_Failure(qSM_Handler_t fsm){

}


static void BlinkColor(Colores_t color , float time){
	static qSTimer_t TimeoutClick = QSTIMER_INITIALIZER;
	static uint8_t toggle = 0;

	if (time != 0){
		if (qSTimer_FreeRun(&TimeoutClick, time )){
			toggle = !toggle;
			BSP_GPIO_DISPLAY_COLOR_RGB( toggle == 1 ? color : COLOR_RGB_BLACK );
		}
	}else{ //time 0.0 no blibk led on
		BSP_GPIO_DISPLAY_COLOR_RGB( color );
	}


}

