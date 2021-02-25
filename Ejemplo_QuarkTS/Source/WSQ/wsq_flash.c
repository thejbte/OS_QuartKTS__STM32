/**
 ********************************************************************************
 *@file wsq_flash.h
 *@brief internal flash API for store data configuration
 *@date Aug 25, 2020
 *@author Esp.Ing.Julian Bustamante N
 ********************************************************************************/

#include "wsq_flash.h"
#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal_flash.h"


#include <string.h>

/**
 * @brief This function  write in sector specified
 * @param Flash_Address init address sector memory
 * @param Flash_Data Data to store
 * @param TypeProgram FLASH_TYPEPROGRAMDATA_BYTE, FLASH_TYPEPROGRAM_HALFWORD or FLASH_TYPEPROGRAM_WORD
 */
static void Flash_Write(uint32_t Flash_Address, uint32_t Flash_Data, uint32_t TypeProgram);

/*
 * Data EEPROM  0x0808 0000 - 0x0808 0BFF  6 Kbytes - Data EEPROM Bank 1
				0x0808 0C00 - 0x0808 17FF            - Data EEPROM Bank 2
 * */


 // @example WSQ_RestoreDataFlash(WSQ_ADDR_RESERVED_DATA_CONFIG,WSQ_FLASH_RESTORE_DATA_CONFIG)
void WSQ_RestoreDataFlash(uint32_t address ,_size_t amount){

	HAL_FLASHEx_DATAEEPROM_Unlock();
	 for( _size_t i = 0 ; i <= (amount/sizeof(uint32_t) ) ; i++){
		HAL_FLASHEx_DATAEEPROM_Erase(address + (i<<2) );
	}
	HAL_FLASHEx_DATAEEPROM_Lock();
}

/*
 ** ===================================================================
 **  					Flash_Write and erase EEprom
 **  					 FLASH_TYPEPROGRAMDATA_WORD		(uint32_t)Flash_Data
 ** ===================================================================
 */
static void Flash_Write(uint32_t Flash_Address, uint32_t Flash_Data, uint32_t TypeProgram){
	HAL_FLASHEx_DATAEEPROM_Unlock();
	HAL_FLASHEx_DATAEEPROM_Erase(Flash_Address);

	/*PROG*/
	HAL_FLASHEx_DATAEEPROM_Program(TypeProgram, Flash_Address ,Flash_Data);   /*16 bits halfword*/
	HAL_FLASHEx_DATAEEPROM_Lock();
}

void WSQ_Flash_Write(uint32_t Address, void *pData , _size_t amount){
	uint32_t *bytedata = (uint32_t*)pData;

	 for( _size_t i = 0 ; i <= (amount/sizeof(uint32_t) ) ; i++) {
		 WSQ_Flash_Write_Word(Address + (i<<2), bytedata[i] );
	 }
}

void WSQ_Flash_Read(uint32_t Address, void *pData , _size_t amount){
		memcpy(pData , (void*)(Address),amount);  /*copy n data*/
}


void WSQ_Flash_Write_Word(uint32_t Flash_Address, uint32_t Flash_Data){
	/*FLASH_TYPEPROGRAMDATA_WORD		(uint32_t)Flash_Data*/
	Flash_Write(Flash_Address,Flash_Data,FLASH_TYPEPROGRAMDATA_WORD);
}


uint32_t WSQ_Flash_Read_Word(uint32_t Flash_Address ){
	uint32_t Flash_Data;
	Flash_Data = *( (uint32_t*)Flash_Address);  // de-referenciar
	return Flash_Data;
}

/*ZeroEmpty is 1 if you want to get zero as empty*/
uint8_t WSQ_Flash_IsEmpty(uint32_t Address, _size_t n , int zeroEmpty){
	uint32_t *chk = (uint32_t*)Address;
	uint8_t retVal = 0;
	for( uint32_t i = 0; i <= (n/sizeof(uint32_t)) ; i++){
		if(1 == zeroEmpty){
			retVal = ( (0xFFFFFFFF == *( chk + i)) ||  (0x00000000 == *( chk + i)) );  /*check by 4*/
		}else if(0 == zeroEmpty){
			retVal =  (0xFFFFFFFF == *( chk + i)) ;
		}
		if(0 == retVal){    /*if is writed, is not empty*/
		    break;
		}
	}
	return retVal;
}
