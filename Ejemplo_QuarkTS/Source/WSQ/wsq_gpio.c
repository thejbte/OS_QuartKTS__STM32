/**
 ********************************************************************************
 *@file wsq_gpio.c
 *@brief GPIO API for the  system
 *@date Jun 25, 2020
 *@author Esp.Ing.Julian Bustamante N
 ********************************************************************************/

/* final pcb gpio*/
#include <Debounce.h>
#include "wsq_gpio.h"
#include "stm32l0xx_ll_gpio.h"
#include "stm32l0xx_ll_bus.h"
#include "stm32l0xx_ll_pwr.h"


static DebounceData_t DebounceData;

/*----------------------------- Private functions ---------------------------------*/
static void GPIO_Write(GPIO_TypeDef *GPIOx, uint32_t PinMask, WSQ_bool pinState);

static WSQ_bool GPIO_Read(GPIO_TypeDef *GPIOx, uint32_t PinMask);

static void WSQ_GPIO_DebounceInit(void);

static volatile uint8_t Click  = 0;

 void WSQ_GPIO_Init(void){

	  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /* GPIO Ports Clock Enable */
	  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
	  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);

	  /*--------------CONFIG SIGFOX PINOUT----------------------*/

	  /* PA7 WISOL_RST */
	  LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_7);

	  /* PA8 WISOL_WKUP*/
	  LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_8);


	  /*PA7 PA8*/
	  GPIO_InitStruct.Pin = LL_GPIO_PIN_7  | LL_GPIO_PIN_8 ;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  /*--------------CONFIG WIFI PINOUT----------------------*/

	  /* PA6	WIFI_RST*/
	  LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_6);

	  /*PA5	WIFI_EN*/
	  LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_5);

	  /*PA4	WIFI_GP0 wifi Write command enable*/
	  LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_4);

	  /*PA7 PA8*/
	  GPIO_InitStruct.Pin = LL_GPIO_PIN_4  | LL_GPIO_PIN_5 | LL_GPIO_PIN_6;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  /*--------------CONFIG OTHERS PINOUT----------------------*/

	  /*PA15 USB Det*/
	  GPIO_InitStruct.Pin = LL_GPIO_PIN_15;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  /*PA3 Enable Analog*/
	  LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_3);

	  GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);


	  /*PB13 Enable Sensor*/
	  LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_13);

	  GPIO_InitStruct.Pin = LL_GPIO_PIN_13;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  /*PB12 Acelerometer Int*/
	  //GPIO_InitStruct.Pin = LL_GPIO_PIN_12;
	  //GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	  //GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	 // LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  /*PB11 Batt Alert*/
	 // GPIO_InitStruct.Pin = LL_GPIO_PIN_11;
	 // GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	  //GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  //LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  /*PB10 Rtc int*/
	  //GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
	  //GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	 // GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	 // LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  /*PB10 Rtc int*/
	 // GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
	 // GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	//  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	//  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  /*PB9 Input digital 1*/
	 // GPIO_InitStruct.Pin = LL_GPIO_PIN_9;
	//  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	//  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	//  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  /*PB8 Input digital 2*/
	//  GPIO_InitStruct.Pin = LL_GPIO_PIN_8;
	//  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	//  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	//  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  /*PB14 Charging status pmic-batt stat*/
	  GPIO_InitStruct.Pin = LL_GPIO_PIN_14;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  /*PB0,PB1,PB2 LedBlue 0, LedGreen 1 , ledRed 2*/
	  LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_8);
	  LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_9);
	  LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_10);

	  GPIO_InitStruct.Pin = LL_GPIO_PIN_8 | LL_GPIO_PIN_9 |  LL_GPIO_PIN_10;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  /*PB5 DO CTRL*/
	  LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_5);

	  GPIO_InitStruct.Pin = LL_GPIO_PIN_5;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  /*Clock wake up*/
	  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
	  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);

	  /*Wake up pin button or reed sw*/
	  LL_PWR_EnableWakeUpPin(LL_PWR_WAKEUP_PIN1);
	  /*Wake up sensors*/
	  LL_PWR_EnableWakeUpPin(LL_PWR_WAKEUP_PIN2);

	  WSQ_GPIO_DebounceInit();
 }


 WSQ_bool WSQ_GPIO_ReadWakeUp(void){
	 return GPIO_Read(GPIOA, LL_GPIO_PIN_0);
 }

  WSQ_bool WSQ_GPIO_ReadWakeUpSense(void){
	 return GPIO_Read(GPIOC, LL_GPIO_PIN_13);
 }


 void WSQ_GPIO_DebounceUpdate(void){
	 Debounce_Update(&DebounceData, WSQ_GPIO_ReadWakeUp());
 }

 /*This function get number clicks- bsp*/
 void WSQ_GPIO_DebounceCountClicks(void){
		if(WSQ_GPIO_DebounceGetRising()){
			WSQ_GPIO_DebounceClearRising();
			++Click;
		}
 }
 uint8_t WSQ_GPIO_DebounceGetClicks(void){
	 return Click;
 }

 void WSQ_GPIO_DebounceClearClicks(void){
			Click = 0;
 }

 static void WSQ_GPIO_DebounceInit(void){
	 Debounce_Init(&DebounceData, WSQ_BUTTON_SENSIVITY , PULL_DOWN);
 }


 WSQ_bool WSQ_GPIO_DebounceGetFalling(void){
	 return (WSQ_bool)DebounceData.FlagFalling;
 }


 WSQ_bool WSQ_GPIO_DebounceGetRising(void){
	 return (WSQ_bool)DebounceData.FlagRising;
 }


  void WSQ_GPIO_DebounceClearRising(void){
 	 DebounceData.FlagRising = WSQ_FALSE;
  }


   void WSQ_GPIO_DebounceClearFalling(void){
  	 DebounceData.FlagFalling = WSQ_FALSE;
   }


  void WSQ_GPIO_SigFoxWriteReset(WSQ_bool pinState){
 	 GPIO_Write(GPIOA, LL_GPIO_PIN_7,pinState);
  }


  void WSQ_GPIO_SigFoxWriteWakeUp(WSQ_bool pinState){
	 	 GPIO_Write(GPIOA, LL_GPIO_PIN_8,pinState);
	  }


  void WSQ_GPIO_WiFiWriteReset(WSQ_bool pinState){
	  GPIO_Write(GPIOA, LL_GPIO_PIN_6,pinState);
  }


  void WSQ_GPIO_WiFiWriteEnable(WSQ_bool pinState){
	  GPIO_Write(GPIOA, LL_GPIO_PIN_5,pinState); //
  }


  void WSQ_GPIO_WiFiWriteCommandEnable(WSQ_bool pinState){
	  GPIO_Write(GPIOA, LL_GPIO_PIN_4,pinState);
  }


  WSQ_bool WSQ_GPIO_ReadUsbDet(void){
	  return GPIO_Read(GPIOA, LL_GPIO_PIN_15);
  }


  void  WSQ_GPIO_EnableAnalog(WSQ_bool pinState){
	  GPIO_Write(GPIOA, LL_GPIO_PIN_3,pinState);
  }

  void  WSQ_GPIO_EnableSensors(WSQ_bool pinState){
	  GPIO_Write(GPIOB, LL_GPIO_PIN_13,pinState);  //
  }

/*CHANGE TO READ FROM ADC ARRAY RESISTOR PB0 ADC*/
  WSQ_bool WSQ_GPIO_ReadAccInt(void){
	  //return GPIO_Read(GPIOB, LL_GPIO_PIN_12);
	  return 0;
  }


  WSQ_bool WSQ_GPIO_ReadBatteryAlert(void){
	  //return GPIO_Read(GPIOB, LL_GPIO_PIN_11);
	  return 0;
  }


  WSQ_bool WSQ_GPIO_ReadRTCInt(void){
	 // return GPIO_Read(GPIOB, LL_GPIO_PIN_10);
	  return 0;
  }


  WSQ_bool WSQ_GPIO_ReadDigitalInput1(void){
	 // return GPIO_Read(GPIOB, LL_GPIO_PIN_9);
	  //add code read adc for DI interrupt
	  return 0;
  }


  WSQ_bool WSQ_GPIO_ReadDigitalInput2(void){
	  //return GPIO_Read(GPIOB, LL_GPIO_PIN_8);
	  //add code read adc for DI interrupt
	  return 0;
  }


  WSQ_bool WSQ_GPIO_ReadChargingStatus(void){
	  return GPIO_Read(GPIOB, LL_GPIO_PIN_14);
  }

  /*WSQ_GPIO_DisplayColorRGB(WSQ_RGB_AQUA);*/
  void WSQ_GPIO_DisplayColorRGB(WSQ_Colores_t Color){
	  WSQ_ColorRGB color;
	  color.rgb = Color;   // WSQ_RGB_YELLOW ->6 421 110; es realmente bgr
	  GPIO_Write(GPIOB,LL_GPIO_PIN_8,color.bits.blue);
	  GPIO_Write(GPIOB,LL_GPIO_PIN_9,color.bits.green);
	  GPIO_Write(GPIOB,LL_GPIO_PIN_10,color.bits.red);
  }


  void WSQ_GPIO_WriteOutputCtrl(WSQ_bool pinState){
	  GPIO_Write(GPIOB, LL_GPIO_PIN_5,pinState);
  }


 static void GPIO_Write(GPIO_TypeDef *GPIOx, uint32_t PinMask, WSQ_bool pinState){
	 if(WSQ_TRUE == pinState )
		 LL_GPIO_SetOutputPin(GPIOx, PinMask);
	 else if( WSQ_FALSE == pinState){
		 LL_GPIO_ResetOutputPin(GPIOx, PinMask);
	 }
 }

 static WSQ_bool GPIO_Read(GPIO_TypeDef *GPIOx, uint32_t PinMask){
	 return (WSQ_bool)LL_GPIO_IsInputPinSet(GPIOx, PinMask);
 }
