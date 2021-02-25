
/*!
 * ********************************************************************************
 * @file wsq_rtc.h
 * @author Julian Bustamante N
 * @date Jul 9, 2020
 * @brief real time clock intern API for the  call system.
 **********************************************************************************/

#ifndef INC_WSQ_RTC_H_
#define INC_WSQ_RTC_H_


#include "stm32l072xx.h"
#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal_rtc.h"

#include "stm32l0xx_ll_rtc.h"
#include "stm32l0xx_ll_bus.h"
#include "stm32l0xx_ll_rcc.h"


/*Macro definitions*/

/*VALORES MAXIMOS RTC TIME*/
#define RTC_MAX_HOURS	0x23
#define RTC_MAX_MIN		0x59
#define RTC_MAX_SEG		0x59

/*RTC macro definitions no trabaja con 23:59:59*/
#define REPORTIME_SECOND		0 //59  o 0
#define REPORTIME_MINUTES		60 //59  o 0
#define REPORTIME_HOUR			0//12 //23h o  12h 0m 0s maximo


/**
 * @brief This function reset flags wakeup
 * */
void WSQ_RTC_ClearWkupFlag(void);


/*seconds only have effect if Min== 0  Seg 0- 65535*/
/**
 * @brief This function set time  for wkup in rtc
 * @param Hor: hours [0-18]
 * @param Min: Min [0-1092]
 * @param Sec: Seg [0-65535]
 *  *@note: set time for wake up timer ↓
 * */
void WSQ_RTC_SetTime(uint8_t Hor , uint8_t Min , uint8_t Seg,uint8_t rewrite);

/**
 *@brief This function configure rtc
 */
void WSQ_RTC_Init(void);

/**
 * @brief This Function clear IRQ pending
 * */
void WSQ_RTC_ClearPendingIRQ(void);

/**
 * @brief Convert minutes to seconds
 * @param Min 0-65535
 * @return Seconds
 * */
uint32_t ConvertMinToSeg(uint16_t Min);


/**
 * @brief Convert Hours to seconds
 * @param Hour 0-65535
 * @return Seconds
 * */
uint32_t ConvertHourToSeg(uint16_t Hour);
#endif /* INC_WSQ_RTC_H_ */
