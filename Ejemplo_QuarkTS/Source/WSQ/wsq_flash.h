/**
 ********************************************************************************
 *@file wsq_flash.h
 *@brief internal flash API for store data configuration
 *@date Aug 25, 2020
 *@author Esp.Ing.Julian Bustamante N
 ********************************************************************************/

#ifndef SOURCE_WSQ_WSQ_FLASH_H_
#define SOURCE_WSQ_WSQ_FLASH_H_


#include <stdint.h>
#include <wsq.h>
/*-------------------------------------------
 * 0x08080000 | DATA_CONFIG | DATA_USER		 |  =
 * -------------------------------------------
 * */

/*
 * Data EEPROM  0x0808 0000 - 0x0808 0BFF  6 Kbytes - Data EEPROM Bank 1
				0x0808 0C00 - 0x0808 17FF            - Data EEPROM Bank 2
 * */
#define WSQ_INIT_ADDR_RESERVED_DATA_CONFIG						0x08080000  /*1K - 0x08080000 - 0x080803ff*/

//#define WSQ_INIT_ADDR_RESERVED_DATA_USER						( (WSQ_INIT_ADDR_RESERVED_DATA_CONFIG) + (WSQ_FLASH_MAX_SIZEPAGE_DATA_CONFIG)) /*2K - 0x08080400 - 0x08080BFF*/


#define WSQ_FLASH_MAX_SIZEPAGE_DATA_CONFIG				1024u  /*!<1k in bytes*/
#define WSQ_FLASH_RESTORE_DATA_CONFIG					( (WSQ_FLASH_MAX_SIZEPAGE_DATA_CONFIG) / (4))  /*!< bytes to restore of sector data config -> 1024 bytes , escritos de a 4 bytes. total 256*/
#define WSQ_FLASH_MAX_SIZEPAGE_BYTES					6144u   /*6k-> 6*1024 */
#define WSQ_FLASH_MAX_SIZEPAGE_WORD						((WSQ_FLASH_MAX_SIZEPAGE_BYTES)/(4) ) 	/*!< 6144/4 = 1536 WORDS*/

#define WSQ_FLASH_OFFSET_END_ADDR	20  				/*ultima posición en la flash 0 , 4 , 8, 12*/


/*Prototypes functions*/

/**
 * @brief This function erase all register eeprom word by word
 * @param Flash_Address init address base sector memory
 * @param amount length sector divide in 4. WSQ_FLASH_RESTORE_DATA_CONFIG
 * @example WSQ_RestoreDataFlash(WSQ_ADDR_RESERVED_DATA_CONFIG,WSQ_FLASH_RESTORE_DATA_CONFIG)
 *
 */
void WSQ_RestoreDataFlash(uint32_t address, _size_t amount);

void WSQ_Flash_Write(uint32_t Address, void *pData , _size_t amount);

void WSQ_Flash_Read(uint32_t Address, void *pData , _size_t amount);

/**
 * @brief This function  write in sector specified
 * @param Flash_Address init address sector memory
 * @param Flash_Data Data to store
 * @param TypeProgram FLASH_TYPEPROGRAMDATA_BYTE, FLASH_TYPEPROGRAM_HALFWORD or FLASH_TYPEPROGRAM_WORD
 */
void WSQ_Flash_Write_Word(uint32_t Flash_Address, uint32_t Flash_Data);

/**
 * @brief This function Read the data in the address selected of the memory flash
 * @param Flash_Address init address sector memory
 * @param OffsetWrite position to read, remember what read in word (4 bytes)
 */
uint32_t WSQ_Flash_Read_Word(uint32_t Flash_Address );

/**
 * @brief This function check memory is empty (0xfffffff...)
 * @param Flash_Address init address sector memory
 * @param size sector to check ( sizeof(struct))
 * @param zeroEmpty is 1 if you wanna verify zero as empty too
 * @return 1 if empty or 0 is writed at least 1bytes != 0xff
 */
uint8_t WSQ_Flash_IsEmpty(uint32_t Address, _size_t n , int zeroEmpty);

#endif /* SOURCE_WSQ_WSQ_FLASH_H_ */
