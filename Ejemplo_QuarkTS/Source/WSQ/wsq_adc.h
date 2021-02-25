/**
 ********************************************************************************
 *@file wsq_adc.h
 *@brief ADC API for the  system
 *@date Jun 25, 2020
 *@author Esp.Ing.Julian Bustamante N
 ********************************************************************************/

#ifndef WSQ_ADC_H
#define WSQ_ADC_H

#include "wsq.h"
#include <stdint.h>


/**
 * @brief Initialize the ADC
 */
 void WSQ_ADC_Init(void);

/**
 * @brief Get the new values from the ADCfor the configured channels and update the
 * internal array.
 */
void WSQ_ADC_UpdateAnalog(void);

/**
 * @brief Read single ADC channel
 * @param channel Channel to read
 * 			WSQ_ADC_CHANNEL_1
 * 			WSQ_ADC_CHANNEL_2
 * @return Digital value for the selected channel ADC
 */
 uint16_t WSQ_ADC_ReadSingleChannel(uint8_t channel);

 /**
  * @brief Get voltage ADC
  * @return Voltage value for the channel 1
  */
 uint16_t WSQ_ADC_GetAIN1(void);
    
 /**
  * @brief Get voltage ADC
  * @return Voltage value for the channel 2
  */
 uint16_t WSQ_ADC_GetAIN2(void);

 /**
  * @brief Get voltage ADC-source interrupt
  * @return Voltage value for the channel 3
  */
 uint16_t WSQ_ADC_GetAIN3(void);
#endif /* WSQ_ADC_H */
