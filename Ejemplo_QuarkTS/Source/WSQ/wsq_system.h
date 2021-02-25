/*!
 * ********************************************************************************
 * @file wsq_system.h
 * @author Julian Bustamante N
 * @date Jun 25, 2020
 * @brief CPU and clock API for the  system.
 **********************************************************************************/


#ifndef WSQ_SYSTEM_H
#define WSQ_SYSTEM_H


#include "wsq.h"
#include "wsq_vcp.h"

typedef enum{
	WKUP_SF_RESET =5,		/*SOFTWARE RESET*/
	WKUP_POR_PDR,			/*POWER-ON_RESET (POR) / POWER-DOWN_RESET (PDR)*/
	WKUP_PIN,
	WKUP_TIME,
	WKUP_UNKNOW
}WSQ_WakeUp_Source_enum_t;
typedef struct {
	WSQ_WakeUp_Source_enum_t Source;
}WSQ_WakeUp_Source_t ;


/**
 * @brief Configure the clock module
 */
void WSQ_SYSTEM_ClockInit(void);


/**
 * @brief Function to be called in case an unrecoverable condition occurs. 
 * It will attempt to reset the CPU.
 */
void WSQ_SYSTEM_FatalException(void);


/**
 * @brief Perform a delay. 
 * @param ms Time to wait in milliseconds
 */
void WSQ_SYSTEM_Delay(uint32_t ms);


/**
 * @brief Initialize all the peripherals
 * @param *UART_SigFoxCustomInputHandler pointer to function callback sigfox irq
 * @param *UART_WiFiCustomInputHandler pointer to function callback wifi irq
 *@param *WSQ_VPC_CallbackRxFcn_t pointer to function callback rx usb irq
 */
void WSQ_SYSTEM_LowLevelInit(void (*UART_SigFoxCustomInputHandler)(char) , void (*UART_WiFiCustomInputHandler)(char), WSQ_VPC_CallbackRxFcn_t usercallback);
/**
 * @brief Initialize the wathcdog
 */
void WSQ_SYSTEM_COPInit(void);


/**
 * @brief Feed the watchdog
 */
void WSQ_SYSTEM_FeedCOP(void);

/**
 * @brief entry standby mode
 * @detail consumption 1.8uA - for each input WKUP reset core
 * */
void WSQ_SYSTEM_StandbyCore(void);

/**
 * @brief send software reset
 * */
void WSQ_SYSTEM_ResetSFT(void);

/**
 *@brief	get source event wakeup interrupt
 *@note		call before init rtc
 *@return 	WSQ_Source_Wkup_t enum source reset
 */
WSQ_WakeUp_Source_t WSQ_SYSTEM_GetResetCause(void);
#endif
