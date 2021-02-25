
/*!
 * ********************************************************************************
 * @file wsq_rtc.h
 * @author Esp.Ing.Julian Bustamante N
 * @date Aug 31, 2020
 * @brief real time clock intern API for the   call system.
 **********************************************************************************/

#include <wsq_rtc.h>
#include "stm32l0xx_hal_rtc.h"
#include "stm32l0xx_hal.h"
#include "stm32l0xx_ll_rtc.h"
#include "stm32l0xx_ll_bus.h"
#include "stm32l0xx_ll_rcc.h"

/*Definitions for calibrations manual-try and failure*/
#define RTC_CALIB_MAN_OFFSET_BASE_TIME        1       /*!< lag time for every 30 seconds*/
#define RTC_CALIB_MAN_BASE_TIME             30    /*!< lag time for every 30 seconds*/
#define RTC_CALIB_MAN_MAX_TIME              53136  /*!< 14.76 hours(51136) + offset time = maximun 65534 seg to temporize (18.2h)*/


extern void Error_Handler();

static uint16_t RTC_CalibManual( uint16_t Seg);


/**
 * @brief RTC Initialization Function
 * @param None
 * @retval None
 */
void WSQ_RTC_Init(void)
{


	/* USER CODE BEGIN RTC_Init 0 */

	/* USER CODE END RTC_Init 0 */

	LL_RTC_InitTypeDef RTC_InitStruct = {0};
	LL_RTC_TimeTypeDef RTC_TimeStruct = {0};
	LL_RTC_DateTypeDef RTC_DateStruct = {0};

	/* Peripheral clock enable */
	LL_RCC_EnableRTC();

	/* RTC interrupt Init */
	NVIC_SetPriority(RTC_IRQn, 0);
	NVIC_EnableIRQ(RTC_IRQn);

	/* USER CODE BEGIN RTC_Init 1 */

	/* USER CODE END RTC_Init 1 */
	/** Initialize RTC and set the Time and Date
	 */
	RTC_InitStruct.HourFormat = LL_RTC_HOURFORMAT_24HOUR;
	RTC_InitStruct.AsynchPrescaler = 127;
	RTC_InitStruct.SynchPrescaler = 255;
	LL_RTC_Init(RTC, &RTC_InitStruct);
	/** Initialize RTC and set the Time and Date
	 */
	RTC_TimeStruct.Hours = 0;
	RTC_TimeStruct.Minutes = 0;
	RTC_TimeStruct.Seconds = 0;
	LL_RTC_TIME_Init(RTC, LL_RTC_FORMAT_BCD, &RTC_TimeStruct);
	RTC_DateStruct.WeekDay = LL_RTC_WEEKDAY_MONDAY;
	RTC_DateStruct.Month = LL_RTC_MONTH_JANUARY;
	RTC_DateStruct.Year = 0;
	LL_RTC_DATE_Init(RTC, LL_RTC_FORMAT_BCD, &RTC_DateStruct);
	/** Initialize RTC and set the Time and Date
	 */
	/** Initialize RTC and set the Time and Date
	 */
	//WSQ_RTC_SetTime(Hor,Min,Seg);  /*Hour,min, seg max 18.2h*/


}


void WSQ_RTC_SetTime(uint8_t Hor , uint8_t Min , uint8_t Seg, uint8_t rewrite){
	/** Enable the WakeUp  A.15.3 RM
		 */
		__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
		LL_RTC_ClearFlag_WUT(RTC);
		LL_RTC_DisableWriteProtection(RTC);
		LL_RTC_WAKEUP_SetClock(RTC, LL_RTC_WAKEUPCLOCK_CKSPRE);
		LL_RTC_DisableIT_WUT(RTC);

		if(rewrite) //nuevo
			LL_RTC_WAKEUP_Disable(RTC);//nuevo wutwf =1   counter=0

		if ( LL_RTC_IsActiveFlag_WUTW(RTC) == 0 ){
			HAL_Delay(1);
		}
		/*desfazado 5-6 segundos en 30- para 5(4min 50) min hay que colocarle 6 aprox*/
		LL_RTC_WAKEUP_SetAutoReload(RTC, RTC_CalibManual((uint16_t)ConvertHourToSeg(Hor) + (uint16_t)ConvertMinToSeg(Min) + Seg) );  /*Max seconds 0xffff -1 a 1Hz*/
		//LL_RTC_WAKEUP_SetAutoReload(RTC, RTC_CalibManual( 43200) );  /*Max seconds 0xffff -1 a 1Hz*/

		LL_RTC_EnableIT_WUT(RTC);
		LL_RTC_WAKEUP_Enable(RTC);

		LL_RTC_EnableWriteProtection(RTC);
}

void WSQ_RTC_ClearWkupFlag(void){
	__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);  /*Wkup pin*/
	LL_RTC_ClearFlag_WUT(RTC);			/*pin*/
}

void RTC_IRQHandler(void)
{
	__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
	LL_RTC_ClearFlag_WUT(RTC);
}


void WSQ_RTC_ClearPendingIRQ(void){
	HAL_NVIC_DisableIRQ(RTC_IRQn);
	HAL_NVIC_ClearPendingIRQ(RTC_IRQn);
	HAL_NVIC_EnableIRQ(RTC_IRQn);
}
/*!< Converter minutes in integer to seconds in integer*/
uint32_t ConvertMinToSeg(uint16_t Min){
	uint32_t Sec = Min*60;
	return Sec;
}
/*!< Converter Hours in integer to seconds in integer*/
uint32_t ConvertHourToSeg(uint16_t Hour){
	uint32_t Sec = Hour*3600;
	return Sec;
}


/**
 * @brief This function calibrate rtc wake up timer with try and failure
 * @param Seg: seconds to temporize
 * @note lag time of 7 seconds for every 30 seconds temporize  20 seg en 10 min , 10 seg en 5 min( 4: 50s)
 * */
static uint16_t RTC_CalibManual( uint16_t Seg){
    Seg = Seg > RTC_CALIB_MAN_MAX_TIME ? RTC_CALIB_MAN_MAX_TIME : Seg;   /*upper limit*/
	Seg += ((Seg/RTC_CALIB_MAN_BASE_TIME)*RTC_CALIB_MAN_OFFSET_BASE_TIME) ;  /*5min-> 300+(300/30)*7*/   /*300 +(300/30)*1*/
	return Seg;
}
