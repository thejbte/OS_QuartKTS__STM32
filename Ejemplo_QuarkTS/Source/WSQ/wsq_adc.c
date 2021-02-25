/**
 ********************************************************************************
 *@file wsq_adc.c
 *@brief ADC API for the system
 *@date Aug 20, 2020
 *@author Esp.Ing.Julian Bustamante N
 ********************************************************************************/


#include <stm32l0xx_ll_adc.h>
#include <stm32l0xx_ll_gpio.h>
#include <stm32l0xx_ll_bus.h>

#include <wsq_adc.h>
#include <stdbool.h>
/*============================================================================
 * Private definitions
 *============================================================================*/
#define WSQ_ADC_CHS      3           /*!< Number of ADC channels configured */
#define WSQ_ADC_VREF	 330          /*!< Vdd = VREF*/
#define WSQ_ADC_MAX_VAL  4095        /*!< 12-bit ADC max value */
#define WSQ_ADC_CHANNEL_1	0		/*!< ADC1 channel 1*/
#define WSQ_ADC_CHANNEL_2	1		/*!< ADC1 channel 2*/
#define WSQ_ADC_CHANNEL_3	2		/*!< ADC1 channel 2*/
#define WSQ_ADC_RETRIES  10000000U   /*!< Number of attempts to get a valid conversion from the ADC */
static volatile uint16_t AnalogVal[WSQ_ADC_CHS] = {0}; /*!< Array to hold the read ADC values */

void WSQ_ADC_Init(void){
	  /* USER CODE BEGIN ADC_Init 0 */

	  /* USER CODE END ADC_Init 0 */

	  LL_ADC_REG_InitTypeDef ADC_REG_InitStruct = {0};
	  LL_ADC_InitTypeDef ADC_InitStruct = {0};

	  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /* Peripheral clock enable */
	  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);

	  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
	  /**ADC GPIO Configuration
	  PA1   ------> ADC_IN1
	  PA2   ------> ADC_IN2
	  */
	  GPIO_InitStruct.Pin = LL_GPIO_PIN_1;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  /**ADC GPIO Configuration
	    PB0   ------> ADC_IN8
	    */
	    GPIO_InitStruct.Pin = LL_GPIO_PIN_0;
	    GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
	    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  /* USER CODE BEGIN ADC_Init 1 */

	  /* USER CODE END ADC_Init 1 */
	  /** Configure Regular Channel
	  */
	  LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_1);
	  /** Configure Regular Channel
	  */
	  LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_2);

	  LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_8);
	  /** Common config
	  */
	  ADC_REG_InitStruct.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
	  ADC_REG_InitStruct.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
	  ADC_REG_InitStruct.ContinuousMode = LL_ADC_REG_CONV_SINGLE;
	  ADC_REG_InitStruct.DMATransfer = LL_ADC_REG_DMA_TRANSFER_NONE;
	  ADC_REG_InitStruct.Overrun = LL_ADC_REG_OVR_DATA_PRESERVED;
	  LL_ADC_REG_Init(ADC1, &ADC_REG_InitStruct);
	  LL_ADC_SetSamplingTimeCommonChannels(ADC1, LL_ADC_SAMPLINGTIME_160CYCLES_5);
	  LL_ADC_SetOverSamplingScope(ADC1, LL_ADC_OVS_DISABLE);
	  LL_ADC_REG_SetSequencerScanDirection(ADC1, LL_ADC_REG_SEQ_SCAN_DIR_FORWARD);
	  LL_ADC_SetCommonFrequencyMode(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_CLOCK_FREQ_MODE_HIGH);
	  LL_ADC_DisableIT_EOC(ADC1);
	  LL_ADC_DisableIT_EOS(ADC1);
	  LL_ADC_EnableInternalRegulator(ADC1);
	  ADC_InitStruct.Clock = LL_ADC_CLOCK_SYNC_PCLK_DIV2;
	  ADC_InitStruct.Resolution = LL_ADC_RESOLUTION_12B;
	  ADC_InitStruct.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
	  ADC_InitStruct.LowPowerMode = LL_ADC_LP_AUTOWAIT_AUTOPOWEROFF;
	  LL_ADC_Init(ADC1, &ADC_InitStruct);
	  /* USER CODE BEGIN ADC_Init 2 */
		/* Calibration procedure----------------------------------------*/
		/* Ensure ADEN = 0 */
		if((ADC1->CR & ADC_CR_ADEN) != 0)
			ADC1->CR |= ADC_CR_ADDIS;

		/* Start calibration */
		ADC1->CR |= ADC_CR_ADCAL;

		/* Wait for and clear EOCAL */
		while((ADC1->ISR & ADC_ISR_EOCAL) == 0){
			/*TODO: handle timeout here*/
		}
		ADC1->ISR |= ADC_ISR_EOCAL;
	  /* USER CODE END ADC_Init 2 */
		  /* ADC interrupt Init */
	 // NVIC_SetPriority(ADC1_COMP_IRQn, 0);
	  //NVIC_EnableIRQ(ADC1_COMP_IRQn);

	 // LL_ADC_EnableIT_EOC(ADC1);
}

/*call before that WSQ_ADC_ReadSingleChannel or WSQ_ADC_GetAINx*/
void WSQ_ADC_UpdateAnalog(void){
	
	/* Iterate over the channels */
		/* Start ADC conversion */
	volatile uint32_t retries;
	bool valid;

	/* Iterate over the channels */
	for(int i = 0; i < WSQ_ADC_CHS; i++){
		retries = 0;
		valid = true;

		/* Start ADC conversion */
		LL_ADC_REG_StartConversion(ADC1);

		while(!LL_ADC_IsActiveFlag_EOC(ADC1)){
			if(retries++ > WSQ_ADC_RETRIES){
				valid = false;
				break;
			}
		}

		LL_ADC_ClearFlag_EOC(ADC1);

		if(valid){
			AnalogVal[i] = LL_ADC_REG_ReadConversionData12(ADC1);

		}
	}

}

uint16_t WSQ_ADC_ReadSingleChannel(uint8_t channel){
		return AnalogVal[channel];    /*adc0 -0.4v , adc1 volt ok*/
}

/**/
uint16_t WSQ_ADC_GetAIN1(void){
	return AnalogVal[WSQ_ADC_CHANNEL_1];
	//return (uint16_t)((AnalogVal[WSQ_ADC_CHANNEL_1]*WSQ_ADC_VREF) / WSQ_ADC_MAX_VAL);  /*divide by 100*/
}

uint16_t WSQ_ADC_GetAIN2(void){
	return AnalogVal[WSQ_ADC_CHANNEL_2];
	//return (uint16_t)((AnalogVal[WSQ_ADC_CHANNEL_2]*WSQ_ADC_VREF) / WSQ_ADC_MAX_VAL);  /*divide by 100*/
}

uint16_t WSQ_ADC_GetAIN3(void){
	return AnalogVal[WSQ_ADC_CHANNEL_3];
	//return (uint16_t)((AnalogVal[WSQ_ADC_CHANNEL_2]*WSQ_ADC_VREF) / WSQ_ADC_MAX_VAL);  /*divide by 100*/
}
/*IRQ ADC*/
void ADC1_COMP_IRQHandler(void)
{
	//	static volatile int i=0;
	//	AnalogVal[i++] = LL_ADC_REG_ReadConversionData12(ADC1);
	//	i= i < WSQ_ADC_CHS ? i : 0;
}
