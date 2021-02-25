/**
 ********************************************************************************
 *@file wsq_uart.h
 *@brief UART API for the  system
 *@date Jul 30, 2020
 *@author Esp.Ing.Julian Bustamante N
 ********************************************************************************/
#include "stdlib.h"

#include "stm32l0xx_ll_usart.h"
#include "stm32l0xx_ll_lpuart.h"
#include "stm32l0xx_ll_bus.h"
#include "stm32l0xx_ll_gpio.h"

#include "wsq_uart.h"
#include "wsq.h"

/*TODO: llamar a isr_char_wisol o isr_char_wifi aca o subir dato a una cola y procesarlo en otro lado para no mezclar capaz	*/
/*------------------------- SigFox ------------------------*/


static WSQ_UART_CustomInputHandler_t UART1_RXUserDefined = NULL;

static WSQ_UART_CustomInputHandler_t UART5_RXUserDefined = NULL;

static WSQ_UART_CustomInputHandler_t LPUART1_RXUserDefined = NULL;

void WSQ_UART_SigFoxInit(uint32_t bitRate , WSQ_UART_CustomInputHandler_t CustomCallback){

	LL_USART_InitTypeDef USART_InitStruct = {0};

	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* Peripheral clock enable */
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);

	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
	/**USART1 GPIO Configuration
	  PA9   ------> USART1_TX
	  PA10   ------> USART1_RX
	 */
	GPIO_InitStruct.Pin = LL_GPIO_PIN_9;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_4;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_4;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* USART1 interrupt Init */
	NVIC_SetPriority(USART1_IRQn, 0);
	NVIC_EnableIRQ(USART1_IRQn);

	USART_InitStruct.BaudRate = bitRate;
	USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
	USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
	USART_InitStruct.Parity = LL_USART_PARITY_NONE;
	USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
	LL_USART_Init(USART1, &USART_InitStruct);
	LL_USART_ConfigAsyncMode(USART1);
	LL_USART_Enable(USART1);

	/*Enable interrupt*/
	LL_USART_EnableIT_RXNE(USART1);

	WSQ_UART_SigFoxSetCustomInputHandler(CustomCallback);
}

void WSQ_UART_SigFoxPutChar(void *sp ,  const char c){
	while( WSQ_FALSE == LL_USART_IsActiveFlag_TXE(USART1))
		continue;
	LL_USART_TransmitData8(USART1, c);
}

void WSQ_UART_SigFoxPutString(const char* s){
	while(*s != '\0'){
		WSQ_UART_SigFoxPutChar(NULL, *s++);
	}
}

/*Set custom callback usart1*/
void WSQ_UART_SigFoxSetCustomInputHandler( WSQ_UART_CustomInputHandler_t UserDefinedAction ){
	UART1_RXUserDefined  = UserDefinedAction ;
}

/*TODO: Cuando toco con rx del serial rx del micro se queda activa la isr por un rato, quizas sea ruido pero estabiliza depues*/
void USART1_IRQHandler( void ){

	char dataIn = '\0';
	if ( LL_USART_IsActiveFlag_RXNE(USART1) == 1 ){ /*read data and clear flag*/
		dataIn = LL_USART_ReceiveData8( USART1 );
		//WSQ_UART_SigFoxPutChar('a');
		if( NULL != UART1_RXUserDefined ){
			UART1_RXUserDefined( dataIn  ); /*callback*/
		}
		else{
			/*use other LL handling for the received data */
		}
	}

	if (LL_USART_IsActiveFlag_ORE(USART1) == 1) // Overrun Error
		LL_USART_ClearFlag_ORE(USART1);

	if (LL_USART_IsActiveFlag_NE(USART1) == 1) // Noise Error
		LL_USART_ClearFlag_NE(USART1);

	if (LL_USART_IsActiveFlag_FE(USART1) == 1) // Framing Error
		LL_USART_ClearFlag_FE(USART1);
}

/*------------------------- WiFi ------------------------*/
void WSQ_UART_WiFiInit(uint32_t bitRate , WSQ_UART_CustomInputHandler_t CustomCallback){

	LL_USART_InitTypeDef USART_InitStruct = {0};

	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	// Peripheral clock enable
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART5);

	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
	// USART5 GPIO Configuration
	// PB3   ------> USART5_TX
	// PB4   ------> USART5_RX

	GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_6;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LL_GPIO_PIN_4;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_6;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	NVIC_SetPriority(USART4_5_IRQn, 0);
	NVIC_EnableIRQ(USART4_5_IRQn);


	USART_InitStruct.BaudRate = bitRate;
	USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
	USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
	USART_InitStruct.Parity = LL_USART_PARITY_NONE;
	USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
	LL_USART_Init(USART5, &USART_InitStruct);
	LL_USART_ConfigAsyncMode(USART5);
	LL_USART_Enable(USART5);

	LL_USART_EnableIT_RXNE(USART5);

	WSQ_UART_WiFiSetCustomInputHandler(CustomCallback);
}


void WSQ_UART_WiFiPutChar(void *sp , const char c){

	while( WSQ_FALSE == LL_USART_IsActiveFlag_TXE(USART5))
		continue;
	LL_USART_TransmitData8(USART5, c);
}

void WSQ_UART_WiFiPutString(const char* s){
	while(*s != '\0'){
		WSQ_UART_WiFiPutChar(NULL , *s++);
	}
}

/*Set custom callback usart1*/
void WSQ_UART_WiFiSetCustomInputHandler( WSQ_UART_CustomInputHandler_t UserDefinedAction ){
	UART5_RXUserDefined  = UserDefinedAction ;
}

void USART4_5_IRQHandler( void ){

	char dataIn = '\0';
	if ( LL_USART_IsActiveFlag_RXNE(USART5) == 1 ){ /*read data and clear flag*/
		dataIn = LL_USART_ReceiveData8( USART5 );
		if( NULL != UART5_RXUserDefined ){
			UART5_RXUserDefined( dataIn  ); /*callback*/
		}
		else{
			/*use other LL handling for the received data */
		}
	}



	if (LL_USART_IsActiveFlag_ORE(USART5) == 1) // Overrun Error
		LL_USART_ClearFlag_ORE(USART5);

	if (LL_USART_IsActiveFlag_NE(USART5) == 1) // Noise Error
		LL_USART_ClearFlag_NE(USART5);

	if (LL_USART_IsActiveFlag_FE(USART5) == 1) // Framing Error
		LL_USART_ClearFlag_FE(USART5);

}


/*------------------------- Debug ------------------------*/
/*No working Debug ?????????????????????????????????????*/
void WSQ_UART_DebugInit(uint32_t bitRate , WSQ_UART_CustomInputHandler_t CustomCallback){

	LL_LPUART_InitTypeDef LPUART_InitStruct = {0};

	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* Peripheral clock enable */
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_LPUART1);

	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
	/**LPUART1 GPIO Configuration
	  PA13   ------> LPUART1_RX
	  PA14   ------> LPUART1_TX
	 */
	GPIO_InitStruct.Pin = LL_GPIO_PIN_13;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_6;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LL_GPIO_PIN_14;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_6;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* USER CODE BEGIN LPUART1_Init 1 */

	/* USER CODE END LPUART1_Init 1 */
	LPUART_InitStruct.BaudRate = bitRate;
	LPUART_InitStruct.DataWidth = LL_LPUART_DATAWIDTH_8B;
	LPUART_InitStruct.StopBits = LL_LPUART_STOPBITS_1;
	LPUART_InitStruct.Parity = LL_LPUART_PARITY_NONE;
	LPUART_InitStruct.TransferDirection = LL_LPUART_DIRECTION_TX_RX;
	LPUART_InitStruct.HardwareFlowControl = LL_LPUART_HWCONTROL_NONE;
	LL_LPUART_Init(LPUART1, &LPUART_InitStruct);
	/* USER CODE BEGIN LPUART1_Init 2 */

	LL_LPUART_Enable(LPUART1);
	//NVIC_SetPriority(RNG_LPUART1_IRQn, 0);
	//NVIC_EnableIRQ(RNG_LPUART1_IRQn);

	// LL_USART_EnableIT_RXNE(LPUART1);

	WSQ_UART_DebugSetCustomInputHandler(CustomCallback);
	/* USER CODE END LPUART1_Init 2 */


}


void WSQ_UART_DebugPutChar(void *sp , const char c){

	while( WSQ_FALSE == LL_LPUART_IsActiveFlag_TXE(LPUART1))
		continue;
	LL_LPUART_TransmitData8(LPUART1, c);

}

void WSQ_UART_DebugPutString(const char* s){
	while(*s != '\0'){
		WSQ_UART_DebugPutChar(NULL , *s++);
	}
}

/*Set custom callback usart1*/
void WSQ_UART_DebugSetCustomInputHandler( WSQ_UART_CustomInputHandler_t UserDefinedAction ){
	LPUART1_RXUserDefined  = UserDefinedAction ;
}

void RNG_LPUART1_IRQHandler( void ){

	char dataIn = '\0';
	if ( LL_LPUART_IsActiveFlag_RXNE(LPUART1) == 1 ){ /*read data and clear flag*/
		dataIn = LL_LPUART_ReceiveData8( LPUART1 );
		if( NULL != LPUART1_RXUserDefined ){
			LPUART1_RXUserDefined( dataIn  ); /*callback*/
		}
		else{
			/*use other LL handling for the received data */
		}
	}

	if (LL_USART_IsActiveFlag_ORE(LPUART1) == 1) // Overrun Error
		LL_USART_ClearFlag_ORE(LPUART1);

	if (LL_USART_IsActiveFlag_NE(LPUART1) == 1) // Noise Error
		LL_USART_ClearFlag_NE(LPUART1);

	if (LL_USART_IsActiveFlag_FE(LPUART1) == 1) // Framing Error
		LL_USART_ClearFlag_FE(LPUART1);

}


