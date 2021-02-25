/*!
 * ********************************************************************************
 * @file wsq_i2c.h
 * @author Julian Bustamante N
 * @date Jun 25, 2020
 * @brief I2C API for the  system.
 **********************************************************************************/


#ifndef WSQ_I2C_H
#define WSQ_I2C_H


#include "wsq.h"


/**
 * @brief Configure the peripheral
 */
void WSQ_I2C_Init(void);


/**
 * @breif Perform a write operation on the I2C bus
 * @param slaveAddr Slave device address
 * @param data Buffer containing the data to send
 * @param n Number of bytes to send
 * @return WSQ_TRUE on success, WSQ_FALSE otherwise
 */
WSQ_bool WSQ_I2C_Write(uint8_t slaveAddr, uint8_t* data, uint8_t n);


/**
 * @breif Perform a read operation on the I2C bus
 * @param slaveAddr Slave device address
 * @param data Buffer to hold the data
 * @param n Number of bytes to read
 * @return WSQ_TRUE on success, WSQ_FALSE otherwise
 */
WSQ_bool WSQ_I2C_Read(uint8_t slaveAddr, uint8_t* data, uint8_t n);

void WSQ_I2C_Reset( void );
/*borrar???*/
void WSQ_I2C_Transmit(uint8_t Address, void *data, uint8_t amount);

void WSQ_I2C_Receive(uint8_t Address, void *Register, uint8_t amount,uint8_t Sizereg);
#endif
