/*!
 * ********************************************************************************
 * @file sht30.c
 * @author Julian Bustamante N
 * @date Sep 29, 2020
 * @brief Driver sensor SHT30x
 **********************************************************************************/

#include <sht30.h>

void SHT30_Init(SHT30_t *obj, SHT30_Write_Fcn_t Write, SHT30_Read_Fcn_t Read, uint8_t Addres_Device){
	obj->Private.Write = Write;
	obj->Private.Read = Read;
	obj->Private.Address = Addres_Device;
}

void SHT30_Write(SHT30_t *obj, uint16_t Reg){
  uint8_t buffer[2];
  
  buffer[0] = (uint8_t)(Reg>>8);
  buffer[1] = (uint8_t)(Reg & 0x00ff);
  obj->Private.Write(obj->Private.Address, (void*)buffer, SHT30_SIZE_REG);
}

void SHT30_Read(SHT30_t *obj, uint16_t Reg, uint8_t amount){
 /*reg Temp Msb|lsb|crc ack Hum msb|Hum|lsb|crc*/
	obj->Private.Read(obj->Private.Address, obj->Private.buffer, amount,1);   /*1 byte 0 dummy to write*/
}

void SHT30_ReadData(SHT30_t *obj){
    uint16_t RawTemp;
    uint16_t RawHum;

	SHT30_Write(obj,SHT30_CMD_CLOCK_STRETCH_H);  /*clock stretching  , COMMAND MEASURE AND HIGH REPEATIBILITY*/
    SHT30_Read(obj, 0x00,SHT30_MAX_DATA_READ);

    RawTemp = (uint16_t)(obj->Private.buffer[0]<<8 | obj->Private.buffer[1]);
    RawHum = (uint16_t)(obj->Private.buffer[3]<<8 | obj->Private.buffer[4]);
    obj->temperature =  (float)(-45 + 175*(RawTemp/(65535.0)) );
    obj->humidity =  (float)(100*(RawHum/(65535.0)));
}

