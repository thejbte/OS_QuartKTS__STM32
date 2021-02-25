/*!
 * ********************************************************************************
 * @file main.c
 * @author Julian Bustamante N
 * @date Aug 18, 2020
 * @brief application main file.
 **********************************************************************************/

#include <stm32l0xx_hal.h>
#include <stdio.h>
#include <string.h>


#include "AT_commands.h"
#include <bsp_remapping.h>
#include <App.h>
#include <Task_Service_Sigfox.h>


extern AppDataCfg_all_t AppData_Config;

/*Borrar ↓*/
void CustomCallback(char c);


int main(){
	/* System init-------------------------------------------*/
	if(HAL_Init() != HAL_OK)
		BSP_SYSTEM_FATAL_EXCEPTION();

	BSP_SYSTEM_CLOCK_INIT();
	WakeUp_Source = BSP_SYSTEM_GET_RESET_CAUSE();
	HAL_Delay(200);/*for not erase epprom when insert battery AAA*/


	if(BSP_FLASH_ISEMPTY(BSP_FLASH_INIT_ADDR_RESERVED_DATA_CONF , sizeof(AppData_Config),1)){
		BSP_FLASH_WRITE(BSP_FLASH_INIT_ADDR_RESERVED_DATA_CONF,&AppData_Config , sizeof(AppData_Config));
	}else{
		BSP_FLASH_READ(BSP_FLASH_INIT_ADDR_RESERVED_DATA_CONF,&AppData_Config,sizeof(AppData_Config));
	}

	BSP_SYSTEM_LL_INIT(Service_Sigfox_ISRHandler,NULL,AT_CLI_CustomCallback);
	BSP_RTC_SET_TIME(AppData_Config.time.hour,AppData_Config.time.min,AppData_Config.time.sec,0) ;
	BSP_GPIO_DISPLAY_COLOR_RGB( AppData_Config.Pulsation_1.rgb); /*while wait delay turn on led*/


	//BSP_FUEL_GAUGE_INIT(BSP_I2C_TRANSMIT ,BSP_I2C_RECEIVE);

	BSP_SENSOR_TH_INIT(BSP_I2C_TRANSMIT ,BSP_I2C_RECEIVE);

	/* Pass control to the scheduler */

	qTrace_Set_OutputFcn(BSP_UART_DEBUG_PUTC);  /*debug by usb*/

	ProjectInformation(0);
	qOS_Setup(NULL, 0.001, App_Task_Idle);
	Service_Sigfox_Setup(AppData_Config.RCZ, BSP_SIGFOX_WRITE_RESET,
			BSP_SIGFOX_WRITE_WAKUP,
			BSP_UART_SIGFOX_PUTC,
			HAL_GetTick);

	Service_Sigfox_Init(NULL, AppData_Config.RCZ , 0 , AppData_Config.redundanciaIsActive);

	/*FSM*/
	qOS_Add_StateMachineTask(&TaskApplicationFSM, qMedium_Priority, APP_CONFIG_TIME_FSM, &ApplicationFSM, App_State_CheckConditions, NULL,NULL , App_State_Failure, NULL, qEnabled, NULL);
	qOS_Add_Task(&TaskHandlerEvents_Scan,App_Task_ScanAndEvents_Callback, qMedium_Priority, 1, qPeriodic, qDisabled, NULL);

	qDebug_Decimal(WakeUp_Source.Source);

	AT_Command_Init();

	qOS_Run();





/* TODO: add wakeup source DI , change resistor and calibrate*/
	while(1){

	}

	return 0;
}

/*Borrar ↓*/
void CustomCallback(char c){

}


