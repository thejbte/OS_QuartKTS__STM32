/*!
 * ********************************************************************************
 * @file sht30.h
 * @author Julian Bustamante N
 * @date Sep 29, 2020
 * @brief Driver sensor SHT30x
 **********************************************************************************/

#ifndef SOURCE_SHT30_H_
#define SOURCE_SHT30_H_

#include <stdint.h>
#include <stdlib.h>

#define SHT30_REV		      "1.0.0"
#define SHT30_CAPTION     "SHT30_REV " SHT30_REV

#define SHT30_SIZE_REG						(0x02)
#define SHT30_ADDR_SLAVE_7BITS            	(( 0x44u ))
#define SHT30_ADDR_SLAVE                   	(( SHT30_ADDR_SLAVE_7BITS << 1 ))  /*0X88*/
#define SHT30_MAX_DATA_READ               	 6  /*!< Temp MSB|LSB|CRC Hum MSB|LSB|CRC*/


typedef enum{
	SHT30_CMD_CLOCK_STRETCH_H = 0x2C06,
	SHT30_CMD_CLOCK_STRETCH_M = 0x2C0D,
	SHT3D_CMD_CLOCK_STRETCH_L = 0x2C10,

	SHT30_CMD_POLLING_H = 0x2400,
	SHT30_CMD_POLLING_M = 0x240B,
	SHT30_CMD_POLLING_L = 0x2416
}SHT31D_Commands;
/**
 * Pointer to functions type
 */
typedef void (*SHT30_Write_Fcn_t )(uint8_t, void*, uint8_t);
typedef void (*SHT30_Read_Fcn_t  )(uint8_t, void*, uint8_t ,uint8_t);

/**
 * @brief structure containing all data
 */
typedef struct {
	struct sht30_private_t{
		SHT30_Write_Fcn_t Write;
		SHT30_Read_Fcn_t  Read;
		uint8_t   Address;  /*7 BITS*/
		uint8_t buffer[SHT30_MAX_DATA_READ];
	}Private;
	float 	temperature , humidity;
}SHT30_t;

/*@brief initialize instance of driver
 *@param obj structure containing all data
 *@param Write pointer to function that writei2c
 *@param Read	pointer to function that readi2c
 *@param Addres_Device	address slave
 * */
void SHT30_Init(SHT30_t *obj, SHT30_Write_Fcn_t Write, SHT30_Read_Fcn_t Read, uint8_t Addres_Device);

void SHT30_Write(SHT30_t *obj, uint16_t Reg);

void SHT30_Read(SHT30_t *obj, uint16_t Reg, uint8_t amount);

/*@brief read data temperature and humidity
 *@param obj structure containing all data
 *obj->temperature and obj->humidity are data readed
 * */
void SHT30_ReadData(SHT30_t *obj);





/*
 ** ===================================================================
 **  Functions Wrappers -  HAl_I2C STM32
 ** ===================================================================
 */
/*void WSQ_I2C_Transmit(uint8_t Address, void *data, uint8_t amount){
	uint8_t *DatatoSend = (uint8_t *)data;
	WSQ_I2C_Write(Address, DatatoSend, amount);
}*/

/*void WSQ_I2C_Receive(uint8_t Address, void *Register, uint8_t amount){
	uint8_t *DatatoSend = (uint8_t *)Register;
	WSQ_I2C_Transmit(Address, DatatoSend, amount);
	WSQ_I2C_Read(Address, DatatoSend, amount);
	LL_I2C_GenerateStopCondition(I2C1);
}*/

/*use:
 * in main.c
 *
 *	SHT30_Init(&SHT30, WSQ_I2C_Transmit2, WSQ_I2C_Receive2, SHT30_ADDR_SLAVE);
 *
 *	SHT30_ReadData(&SHT30);
	qDebug_Float(SHT30.temperature);
	qDebug_Float(SHT30.humidity);

 * */
#endif  /* SOURCE_SHT30_H_ */
