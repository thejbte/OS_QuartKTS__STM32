/*!
 * ********************************************************************************
 * @file wsq_vcp.h
 * @author Julian Bustamante N
 * @date Jun 25, 2020
 * @brief Virtual Comm Port API for the  system.
 **********************************************************************************/


#ifndef WSQ_VCP_H
#define WSQ_VCP_H


#include "wsq.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

extern USBD_HandleTypeDef hUsbDeviceFS;

/*@brief pointer to callback data usb received
 * @param  Buf: Buffer of data to be received
 * @param  Len: Number of data received (in bytes)
 * */
typedef void (*WSQ_VPC_CallbackRxFcn_t)(uint8_t* , uint32_t);

/**
 * @brief Initialize the Virtual Comm Port.
 * @param CustomCallbackRx: callback defined by user for data receive
 */
void WSQ_VCP_Init(WSQ_VPC_CallbackRxFcn_t CustomCallbackRx);

/**
 * @brief Write a message over the console interface.
 * @param msg Null terminated string to write.
 *
 */
void WSQ_VCP_Print(uint8_t* msg );


/*@brief USB Transmission char
 *@param sp pointer empty
 *@param c char to write */
void WSQ_VPC_PutChar( void *sp, const char c );


#endif
