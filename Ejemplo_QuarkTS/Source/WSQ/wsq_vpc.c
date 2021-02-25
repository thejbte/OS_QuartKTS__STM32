
/*!
 * ********************************************************************************
 * @file wsq_vcp.c
 * @author Esp.Ing.Julian Bustamante N
 * @date Aug 20, 2020
 * @brief Virtual Comm Port API for the  system.
 **********************************************************************************/

#include "wsq_vcp.h"


/*Nota: Se debe Optimizar el proyecto -Os para que no falle el stack usb y se desconecte solo.
 * 		-Se debe Modificar usbd_cdc_if.c CDC_Control_FS in CDC_SET_CONTROL_LINE_STATE solo en windows
 * */

/*============================================================================
 * Definitions and variables
 *============================================================================*/
#define WSQ_VCP_RX_DATA_SIZE  1000

uint8_t UserRxBuffer[WSQ_VCP_RX_DATA_SIZE + 1];
extern uint8_t UserRxBufferFS[WSQ_VCP_RX_DATA_SIZE + 1];
volatile bool WSQ_VCP_RxReady = false;

volatile uint8_t host_com_port_open;

WSQ_VPC_CallbackRxFcn_t WSQ_VPC_CallbackRXUserDefined = NULL;



/*============================================================================
 * API implementation
 *============================================================================*/

void WSQ_VCP_Init(WSQ_VPC_CallbackRxFcn_t CustomCallbackRx){
	WSQ_VPC_CallbackRXUserDefined = CustomCallbackRx;
	MX_USB_DEVICE_Init();
}


/*@brief USB Transmission buffer*/
void WSQ_VCP_Print(uint8_t* msg ){
		uint16_t Len = strlen((const char*)msg);
		if(CDC_Transmit_FS(msg, Len) != USBD_OK){

		}
}


/*@brief USB Transmission char*/
void WSQ_VPC_PutChar( void *sp, const char c ){
	while( ( ( CDC_Transmit_FS((uint8_t*)&c, 1)) == USBD_BUSY)  &&  host_com_port_open && (hUsbDeviceFS.dev_state == USBD_STATE_CONFIGURED) ); /*put the char in the output buffer and wait until transmit is complete*/

}



