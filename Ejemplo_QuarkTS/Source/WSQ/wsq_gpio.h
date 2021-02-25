/**
 ********************************************************************************
 *@file wsq_gpio.h
 *@brief GPIO API for the  system
 *@date Jun 25, 2020
 *@author Esp.Ing.Julian Bustamante N
 ********************************************************************************/

#ifndef WSQ_GPIO_H
#define WSQ_GPIO_H


#include "wsq.h"
#include "stm32l0xx_ll_pwr.h"
#include "stm32l0xx_ll_cortex.h"



/**
 * @brief This function read state of pin wake up ( button or reed switch)
 * @return state pin ( WSQ_FALSE or  WSQ_TRUE)
*/
WSQ_bool WSQ_GPIO_ReadWakeUp(void);


 WSQ_bool WSQ_GPIO_ReadWakeUpSense(void);

/**
 * @brief This function update counter debounce for pin wake up
 * 	Debounce_Update(&DebounceData, WSQ_GPIO_ReadWakeUp());
*/
void WSQ_GPIO_DebounceUpdate(void);

/** @brief This function count number clicks- bsp
 * */
void WSQ_GPIO_DebounceCountClicks(void);

/** @brief This function get number clicks- bsp
 * @return clicks by rising edge ( auto clear rising edge)
 * */
uint8_t WSQ_GPIO_DebounceGetClicks(void);

/** @brief This function clear clicks- bsp
 */
void WSQ_GPIO_DebounceClearClicks(void);


/**
 * @brief this function get state of falling edge
 * @return state falling edge ( WSQ_FALSE or  WSQ_TRUE)
*/
WSQ_bool WSQ_GPIO_DebounceGetFalling(void);


/**
 * @brief this function get state of rising endge
 * @return state rising edge ( WSQ_FALSE or  WSQ_TRUE)
*/
WSQ_bool WSQ_GPIO_DebounceGetRising(void);

/**
  * @brief this function clear flag of rising edge
 */
 void WSQ_GPIO_DebounceClearRising(void);

 /**
   * @brief this function clear flag of falling edge
  */
  void WSQ_GPIO_DebounceClearFalling(void);

/**
 * @brief Initialize GPIO configuration
 */
 void WSQ_GPIO_Init(void);

 
/**
 * @brief Reset the Wisol communication module
 * @param pinState value to write 
 */
 void WSQ_GPIO_SigFoxWriteReset(WSQ_bool pinState);

 
/**
 * @brief Wake up the Wisol module
 * @param pinState value to write
 */
 void WSQ_GPIO_SigFoxWriteWakeUp(WSQ_bool pinState);

 
/**
 * @brief Reset the WI-FI module
 * @param pinState value to write
 */
 void WSQ_GPIO_WiFiWriteReset(WSQ_bool pinState);

 
/**
 * @brief Enable the WiFi module
 * @param pinState value to write
 */
 void WSQ_GPIO_WiFiWriteEnable(WSQ_bool pinState);

 
/**
 * @brief Control the WiFi module command mode
 * @param pinState value to write
 */
 void WSQ_GPIO_WiFiWriteCommandEnable(WSQ_bool pinState);    

 
/**
 * @brief Read the state of the USB connection
 * @return Connection state
 */
 WSQ_bool WSQ_GPIO_ReadUsbDet(void);    

 
/**
 * @brief Enable the analog inputs
 * @param pinState WSQ_TRUE to enable, WSQ_FALSE otherwise
 */
 void  WSQ_GPIO_EnableAnalog(WSQ_bool pinState);

 
/**
 * @brief Enable the sensors subsystem
 * @param pinState WSQ_TRUE to enable, WSQ_FALSE otherwise
 */
 void  WSQ_GPIO_EnableSensors(WSQ_bool pinState);

 
/**
 * @brief Read accelerometer interrupt status
 * @return Accelerometer interrupt state
 */
 WSQ_bool WSQ_GPIO_ReadAccInt(void);  

 
/**
 * @brief Read battery alert pin from fuel gauge
 * @return Fuel gauge alert state
 */
 WSQ_bool WSQ_GPIO_ReadBatteryAlert(void);  

 
/**
 * @brief Read the RTC interrupt status
 * @return RTC interrupt status
 */
 WSQ_bool WSQ_GPIO_ReadRTCInt(void);


/**
 * @brief Read the state of the digital input 1
 * @return Digital input 1 state
 */
 WSQ_bool WSQ_GPIO_ReadDigitalInput1(void);

 
/**
 * @brief Read the state of the digital input 2
 * @return Digital input 2 state
 */
 WSQ_bool WSQ_GPIO_ReadDigitalInput2(void);
 
 
/**
 * @brief Read charging status
 * @return Charging status value
 */
 WSQ_bool WSQ_GPIO_ReadChargingStatus(void);

 
/**
 * @brief Display a color on the RGB LED
 * @param color RGB color to display
 */
 void WSQ_GPIO_DisplayColorRGB(WSQ_Colores_t Color);
 

/**
 * @brief Write the output control signal
 * @param state Value to write
 */
 void WSQ_GPIO_WriteOutputCtrl(WSQ_bool pinState);
    
#endif /* WSQ_GPIO_H */

