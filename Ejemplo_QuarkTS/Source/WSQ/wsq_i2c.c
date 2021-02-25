/*!
 * ********************************************************************************
 * @file wsq_i2c.c
 * @author Julian Bustamante N
 * @date Aug 18, 2020
 * @brief I2C API for the  system.
 **********************************************************************************/

#include <wsq_i2c.h>
#include <wsq_system.h>
#include <stm32l0xx_ll_i2c.h>
#include <stm32l0xx_ll_bus.h>
#include <stm32l0xx_ll_gpio.h>

/* Private definitions -----------------------------------------------------------*/
#define WSQ_I2C_MAX_READ_RET   200000    /*!< Number of attempts to read the data register */
#define WSQ_I2C_MAX_WRITE_RET   200000

void WSQ_I2C_Init(){
	LL_I2C_InitTypeDef i2cInit = {0};
	LL_GPIO_InitTypeDef gpioInit = {0};

	/* I2C 1 Initialization-----------------------------------------------------*/
	/* Peripheral clock enable */
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);

	/**I2C1 GPIO Configuration
	PB6   ------> I2C1_SCL
	PB7   ------> I2C1_SDA
	*/
	gpioInit.Pin = LL_GPIO_PIN_6;
	gpioInit.Mode = LL_GPIO_MODE_ALTERNATE;
	gpioInit.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	gpioInit.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
	gpioInit.Pull = LL_GPIO_PULL_NO;
	gpioInit.Alternate = LL_GPIO_AF_1;
	LL_GPIO_Init(GPIOB, &gpioInit);

	gpioInit.Pin = LL_GPIO_PIN_7;
	gpioInit.Mode = LL_GPIO_MODE_ALTERNATE;
	gpioInit.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	gpioInit.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
	gpioInit.Pull = LL_GPIO_PULL_NO;
	gpioInit.Alternate = LL_GPIO_AF_1;
	LL_GPIO_Init(GPIOB, &gpioInit);

	/* Automatic STOP condition */
	//LL_I2C_EnableAutoEndMode(I2C1);
	LL_I2C_DisableAutoEndMode(I2C1);


	LL_I2C_DisableOwnAddress2(I2C1);
	LL_I2C_DisableGeneralCall(I2C1);

	/* Clock stretching must be enabled in master mode */
	LL_I2C_EnableClockStretching(I2C1);

	i2cInit.PeripheralMode = LL_I2C_MODE_I2C;
	i2cInit.Timing = 0x00303D5B ; /* Value calculated by the code generator 100 khz  - 0x0010061A ->400khz*/
	i2cInit.AnalogFilter = LL_I2C_ANALOGFILTER_ENABLE;
	i2cInit.DigitalFilter = 0;
	i2cInit.OwnAddress1 = 0;
	i2cInit.TypeAcknowledge = LL_I2C_ACK;
	i2cInit.OwnAddrSize = LL_I2C_OWNADDRESS1_7BIT;
	LL_I2C_Init(I2C1, &i2cInit);
	LL_I2C_SetOwnAddress2(I2C1, 0, LL_I2C_OWNADDRESS2_NOMASK);
}


WSQ_bool WSQ_I2C_Write(uint8_t slaveAddr, uint8_t* data, uint8_t n){

	uint32_t retries = 0;
	/* Set slave address */
    LL_I2C_SetSlaveAddr(I2C1, (uint32_t)slaveAddr);

    /* Request a write */
    LL_I2C_SetTransferRequest(I2C1, LL_I2C_REQUEST_WRITE);

	/* Set the number of bytes to transfer */
	LL_I2C_SetTransferSize(I2C1, (uint32_t)n);

	/* At most, 255 bytes are being transmitted */
	//LL_I2C_EnableAutoEndMode(I2C1);

	/* Flag the peripheral to start transmission */
	LL_I2C_GenerateStartCondition(I2C1);
	while(I2C1->CR2 & I2C_CR2_START){
		if(++retries >= WSQ_I2C_MAX_READ_RET)
					return WSQ_FALSE;
	}

	/* Loop until all bytes have been sent */
	for(int i = 0; i < n; i++){
		retries = 0;
		while((!LL_I2C_IsActiveFlag_NACK(I2C1)) && (!LL_I2C_IsActiveFlag_TXIS(I2C1))){
			if(++retries >= WSQ_I2C_MAX_WRITE_RET)
				return WSQ_FALSE;
		}

		if(LL_I2C_IsActiveFlag_NACK(I2C1)){
			LL_I2C_ClearFlag_NACK(I2C1);
			return WSQ_FALSE;
		}

		LL_I2C_TransmitData8(I2C1, data[i]);
	}


	return WSQ_TRUE;
}


WSQ_bool WSQ_I2C_Read(uint8_t slaveAddr, uint8_t* data, uint8_t n){

	uint32_t retries = 0;

	/* Set slave address */
	LL_I2C_SetSlaveAddr(I2C1, (uint32_t)slaveAddr);

	/* Request a read */
	LL_I2C_SetTransferRequest(I2C1, LL_I2C_REQUEST_READ);

	/* Set the number of bytes to transfer */
    LL_I2C_SetTransferSize(I2C1, (uint32_t)n);

	/* At most, 255 bytes are being transmitted */
	//LL_I2C_EnableAutoEndMode(I2C1);

	/* Flag the peripheral to start transmission */
	LL_I2C_GenerateStartCondition(I2C1);

	while(I2C1->CR2 & I2C_CR2_START){
		if(++retries >= WSQ_I2C_MAX_READ_RET)
			return WSQ_FALSE;
	}

	/* Loop until all bytes have been received */

	for(int i = 0; i < n; i++){
		retries = 0;
		while(!LL_I2C_IsActiveFlag_RXNE(I2C1)){
			if(++retries >= WSQ_I2C_MAX_READ_RET)
				return WSQ_FALSE;
		}

		data[i] = LL_I2C_ReceiveData8(I2C1);
	}


	return WSQ_TRUE;

}
void WSQ_I2C_Reset( void ){
	LL_I2C_DeInit( I2C1 );
	WSQ_I2C_Init();
	WSQ_SYSTEM_Delay(20);
}

/*
 ** ===================================================================
 **  Functions Wrappers -  HAl_I2C STM32
 ** ===================================================================
 */
void WSQ_I2C_Transmit(uint8_t Address, void *data, uint8_t amount){
	uint8_t *DatatoSend = (uint8_t *)data;
	WSQ_I2C_Write(Address, DatatoSend, amount);
}

void WSQ_I2C_Receive(uint8_t Address, void *Register, uint8_t amount,uint8_t Sizereg){
	uint8_t *DatatoSend = (uint8_t *)Register;
	WSQ_I2C_Transmit(Address, DatatoSend, Sizereg);
	WSQ_I2C_Read(Address, DatatoSend, amount);
	LL_I2C_GenerateStopCondition(I2C1);  /*stop manually*/
}
