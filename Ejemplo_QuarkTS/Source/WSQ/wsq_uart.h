/**
 ********************************************************************************
 *@file wsq_uart.h
 *@brief UART API for the  system
 *@date Jun 25, 2020
 *@author Esp.Ing.Julian Bustamante N
 ********************************************************************************/

#ifndef WSQ_UART_H
#define WSQ_UART_H

#include "wsq.h"
#include <stdint.h>

/*pointer to function for callback uart */
typedef void (*WSQ_UART_CustomInputHandler_t)(const char);

/**
 * @brief Initialize the UART for Sigfox module
 * @param bitRate Desired speed to configure
 */
 void WSQ_UART_SigFoxInit(uint32_t bitRate , WSQ_UART_CustomInputHandler_t CustomCallback);

 /**
 * @brief Send char to the Sigfox module
 * @param c Char to send
 */
 void WSQ_UART_SigFoxPutChar(void *sp , const char c);

/**
 * @brief Send string to the Sigfox module
 * @param s pointer to the null terminated string
 */
 void WSQ_UART_SigFoxPutString(const char* s);

 /**
   * @brief function for upload data to callback Sigfox service
   * */

 void WSQ_UART_SigFoxSetCustomInputHandler( WSQ_UART_CustomInputHandler_t UserDefinedAction );

/**
 * @brief Initialize the UART for the WiFi module
 * @param bitRate Desired speed to configure
 */
 void WSQ_UART_WiFiInit(uint32_t bitRate, WSQ_UART_CustomInputHandler_t CustomCallback);

/**
 * @brief Send char to the WiFi module
 * @param c Char to send
 */
 void WSQ_UART_WiFiPutChar(void *sp ,const char c);

/**
 * @brief Send string to the WiFi module
 * @param s pointer to the null terminated string
 */
 void WSQ_UART_WiFiPutString(const char* s);
    
 /**
  * @brief function for upload data to callback wifi
  * */
 void WSQ_UART_WiFiSetCustomInputHandler( WSQ_UART_CustomInputHandler_t UserDefinedAction );


 /**
  * @brief Initialize the UART for the debug
  * @param bitRate Desired speed to configure
  */
  void WSQ_UART_DebugInit(uint32_t bitRate, WSQ_UART_CustomInputHandler_t CustomCallback);

 /**
  * @brief Send char to the debug
  * @param c Char to send
  */
  void WSQ_UART_DebugPutChar(void *sp ,const char c);

 /**
  * @brief Send string to the debug
  * @param s pointer to the null terminated string
  */
  void WSQ_UART_DebugPutString(const char* s);

  /**
   * @brief function for upload data to callback debug rx
   * */
  void WSQ_UART_DebugSetCustomInputHandler( WSQ_UART_CustomInputHandler_t UserDefinedAction );

#endif /* WSQ_UART_H */

