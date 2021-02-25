/*!
 * ********************************************************************************
 * @file WSQ_system.h
 * @author Julian Bustamante N
 * @date Aug 31, 2020
 * @brief CPU and clock API for the  system.
 **********************************************************************************/

#include <wsq.h>
#include <wsq_system.h>
#include <wsq_gpio.h>
#include <wsq_vcp.h>
#include <wsq_i2c.h>
#include <wsq_uart.h>
#include <wsq_adc.h>
#include <wsq_rtc.h>
#include <stm32l0xx_ll_system.h>
#include <stm32l0xx_ll_pwr.h>
#include <stm32l0xx_ll_rcc.h>
#include <stm32l0xx_ll_bus.h>
#include <stm32l0xx_ll_utils.h>
#include <stm32l0xx_ll_cortex.h>
#include <stm32l0xx_ll_iwdg.h>
#include <stm32l0xx_hal.h>
#include <stm32l0xx_hal_pcd.h>
#include "../QuarkTS/include/qclock.h"

#include "data_cofigurator.h"
extern AppDataCfg_all_t AppData_Config;

/* Compatibility -------------------------------------------------------------*/
void Error_Handler(){
	WSQ_SYSTEM_FatalException();
}


/* External variables --------------------------------------------------------*/
extern PCD_HandleTypeDef hpcd_USB_FS;



/* API implementation ---------------------------------------------------------*/
void SystemClock_Config(void){



	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

	/** Configure the main internal regulator output voltage
	*/
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/** Initializes the CPU, AHB and APB busses clocks
	*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|
			RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSI48;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.LSIState = RCC_LSI_ON;
	RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
	Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	*/
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
							  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
	{
	Error_Handler();
	}
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPUART1|RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1|RCC_PERIPHCLK_USB;
	PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
	PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
	PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PCLK1;
	PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
	PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
	{
	Error_Handler();
	}


}

/*reset software*/
void WSQ_SYSTEM_FatalException(){
	/* Attempt to reset the CPU */
	//SCB->AIRCR = (0x5FA << SCB_AIRCR_VECTKEY_Pos) | SCB_AIRCR_SYSRESETREQ_Msk;
	WSQ_UART_DebugPutString("Fatal exception\r\n");  // borrar
	WSQ_SYSTEM_ResetSFT();
	//while(1);
}


void WSQ_SYSTEM_Delay(uint32_t ms){
	HAL_Delay(ms);
}


void WSQ_SYSTEM_LowLevelInit(void (*UART_SigFoxCustomInputHandler)(char) , void (*UART_WiFiCustomInputHandler)(char), WSQ_VPC_CallbackRxFcn_t usercallback){
	WSQ_GPIO_Init();
	WSQ_ADC_Init();
	WSQ_UART_SigFoxInit(WSQ_SIGFOX_BR, UART_SigFoxCustomInputHandler);
	WSQ_UART_WiFiInit(AppData_Config.idDevice == 1?WSQ_GPS_BR :WSQ_WIFI_BR , UART_WiFiCustomInputHandler);
	WSQ_UART_DebugInit(WSQ_DEBUG_BR, NULL);
	WSQ_VCP_Init(usercallback);
	WSQ_I2C_Init();
	WSQ_RTC_Init();
	//WSQ_SYSTEM_COPInit(); /*TODO: WDT new*/


}

/* About 6.65 seconds se reinicia cuando estadormido source 9*/
void WSQ_SYSTEM_COPInit(){
	//https://www.programmersought.com/article/16664704108/
	uint16_t ctr;

	LL_IWDG_Enable(IWDG);
	LL_IWDG_EnableWriteAccess(IWDG);
	LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_128);  //About 13.107 seconds
	LL_IWDG_SetReloadCounter(IWDG, 0xfff);

	while (LL_IWDG_IsReady(IWDG) != 1){
		if(ctr++ > 10000000)
			WSQ_SYSTEM_FatalException();
	}

	LL_IWDG_SetWindow(IWDG, 0xfff);
	LL_IWDG_ReloadCounter(IWDG);
}

void WSQ_SYSTEM_FeedCOP(){
	LL_IWDG_EnableWriteAccess(IWDG);
	LL_IWDG_ReloadCounter(IWDG);
}

void WSQ_SYSTEM_StandbyCore(void){
	LL_PWR_ClearFlag_WU(); /*Clear Wakeup flag*/
	LL_PWR_SetPowerMode(LL_PWR_MODE_STANDBY);
	LL_LPM_EnableDeepSleep(); //Processor uses deep sleep as its low power mode.
	__WFI(); /*Wait for interrupt*/
}

/* System handlers --------------------------------------------------------*/

void SysTick_Handler(void){
	HAL_IncTick();
	WSQ_KERNEL_TICK();
	WSQ_GPIO_DebounceUpdate();		/*update debounce falling or rising*/
	WSQ_GPIO_DebounceCountClicks();  /*increment number of click- clear rising edge*/
}

void USB_IRQHandler(void){
  HAL_PCD_IRQHandler(&hpcd_USB_FS);
}


void NMI_Handler(void){}


void HardFault_Handler(void){
	WSQ_SYSTEM_FatalException();
}

void WSQ_SYSTEM_ResetSFT(void){
	WSQ_UART_DebugPutString("Software reset!\r\n");
	SCB->AIRCR = (0x5FA << SCB_AIRCR_VECTKEY_Pos) | SCB_AIRCR_SYSRESETREQ_Msk;
	while(1);  /* wait until reset */
}

void SVC_Handler(void){}


void PendSV_Handler(void){}

/* ===================================================================*/
WSQ_WakeUp_Source_t WSQ_SYSTEM_GetResetCause(void){
	static WSQ_WakeUp_Source_t Source_wkup;

	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

	if(LL_RTC_IsActiveFlag_WUT(RTC)  ){
		Source_wkup.Source = WKUP_TIME;
		/*reset flags system reset RCC_FLAG_PINRST, RCC_FLAG_PORRST, RCC_FLAG_SFTRST, RCC_FLAG_OBLRST, RCC_FLAG_IWDGRST, RCC_FLAG_WWDGRST, RCC_FLAG_LPWRRST*/
		LL_RTC_ClearFlag_WUT(RTC);
		LL_RCC_ClearResetFlags();
	}else if ( LL_RCC_IsActiveFlag_SFTRST() ){ /*Reset por software*/
		LL_RCC_ClearResetFlags();
		Source_wkup.Source = WKUP_SF_RESET;
	}else if (LL_RCC_IsActiveFlag_PORRST()){/*Power ON/DOWN*/
		Source_wkup.Source = WKUP_POR_PDR;
		LL_RCC_ClearResetFlags();
	}else if ( LL_PWR_IsActiveFlag_WU()   ){
		Source_wkup.Source = WKUP_PIN;
		LL_PWR_ClearFlag_WU();
		LL_RCC_ClearResetFlags();
	} else {
		Source_wkup.Source = WKUP_UNKNOW;
	}

	return Source_wkup;
}
