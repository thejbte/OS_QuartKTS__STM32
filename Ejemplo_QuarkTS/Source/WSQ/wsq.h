/*!
 * ********************************************************************************
 * @file wsq.h
 * @author Julian Bustamante N
 * @date Jun 26, 2020
 * @brief Configuration an definitions header for the  system API.
 **********************************************************************************/


#ifndef WSQ_H
#define WSQ_H

#include <stdint.h>
#include <stdbool.h>
typedef uint16_t _size_t;

#define WSQ_SYSTEM_ClockInit SystemClock_Config  /*!< clock */

/*----------------------------- Type definitions ---------------------------------*/
/**
 * @brief Custom bool type
 */
 typedef enum{
     WSQ_FALSE = 0,
     WSQ_TRUE
 }WSQ_bool;

/**
 * @brief Color type for the RGB LED
 */
  typedef union{                                                                                                                                                             
    uint8_t rgb;                                                                                                                                                            
    struct{                                                                                                                                                                 
       uint8_t blue:  1;
       uint8_t green: 1;                                                                                                                                                    
       uint8_t red:   1;
    }bits;                                                                                                                                                                  
 }WSQ_ColorRGB;  

 /**
  * @brief specified Color for the RGB LED
  */
 typedef enum {          /*RGB*/
	 COLOR_RGB_BLACK = 0,	 /*#000000 off*/
	 COLOR_RGB_BLUE,		 /*#0000ff*/
	 COLOR_RGB_GREEN,	 	 /*#00ff00*/
	 COLOR_RGB_AQUA,       /*#00FFFF*/
	 COLOR_RGB_RED,			 /*#ff0000*/
	 COLOR_RGB_FUCHSIA,    /*#FF00FF*/
	 COLOR_RGB_YELLOW ,    /*#ffff00*/
	 COLOR_RGB_WHITE,      /*#FFFFFF*/

 }WSQ_Colores_t;

/*----------------------------- Configuration macros -----------------------------*/              
#define  WSQ_KERNEL_TICK()   qClock_SysTick()   /*!< Set this to the particular kernel tick function */
#define  WSQ_SIGFOX_BR       9600                /*!< Default bit rate for the Sigfox interface */
#define  WSQ_WIFI_BR         115200                /*!< Default bit rate for the WiFi interface */
#define  WSQ_GPS_BR          9600                /*!< Default bit rate for the Gps interface */
#define  WSQ_DEBUG_BR        115200                /*!< Default bit rate for the Debug interface */
#define  WSQ_BUTTON_SENSIVITY	20				   /*!< Default sensivity debounce for button or reed sw*/

#endif
