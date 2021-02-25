/*
 * bsp_remapping.h
 *
 * @brief This layer contains macros associated with each method
 * of the low-level layer associated with the peripherals of the
 * micro-controller.
 *
 * services, kernel, tasks and the application will only be able
 * to access these macros to make use of the peripherals.
 *
 * 	@date Sep 8, 2020
 *  @author: MPC - JBN
 */
#ifndef SOURCE_BSP_BSP_REMAPPING_H_
#define SOURCE_BSP_BSP_REMAPPING_H_



/**
 * @brief Includes, associated with the peripheries of the low-level
 * layer
 */

/*ADD INCLUDE*/
#include <wsq.h>
#include <wsq_system.h>
#include <wsq_gpio.h>
#include <wsq_adc.h>
#include <wsq_flash.h>
#include <wsq_i2c.h>
#include <wsq_rtc.h>
#include <wsq_uart.h>
#include <wsq_vcp.h>


#include <sht30.h>

#define _WSQ_
#undef  _SMART_CITIES_
#undef  _LC709203F_
#undef  _MAX17048_
#ifdef _WSQ_

 //MAX17048_t MAX17048;
 SHT30_t SHT30;


typedef WSQ_bool BSP_bool;   /*!< 1 or 0*/
typedef WSQ_ColorRGB 	ColorRGB;
typedef WSQ_Colores_t	Colores_t;

/*begin BSP gpio*/
#define BSP_GPIO_READ_WAKEUP()                      WSQ_GPIO_ReadWakeUp()                   /*!< return enum 0-1 */
#define BSP_GPIO_DEBOUNCE_UPDATE()                  WSQ_GPIO_DebounceUpdate()               /*!< return enum 0-1 */
#define BSP_GPIO_DEBOUNCE_GET_FALLING()             WSQ_GPIO_DebounceGetFalling()           /*!< return enum 0-1 */
#define BSP_GPIO_DEBOUNCE_GET_RISING()              WSQ_GPIO_DebounceGetRising()            /*!< return enum 0-1 */
#define BSP_GPIO_DEBOUNCE_CLEAR_RISING()            WSQ_GPIO_DebounceClearRising()          /*!< return enum 0-1 */
#define BSP_GPIO_DEBOUNCE_CLEAR_FALLING()           WSQ_GPIO_DebounceClearFalling()          /*!< return enum 0-1 */
#define BSP_GPIO_DEBOUNCE_GET_CLICK()				WSQ_GPIO_DebounceGetClicks()			 /*return number of click from isr pin*/
#define BSP_GPIO_DEBOUNCE_CLEAR_CLICK()				WSQ_GPIO_DebounceClearClicks()
#define BSP_GPIO_READ_USBDET()                      WSQ_GPIO_ReadUsbDet()                   /*!< return enum 0-1 */
#define BSP_GPIO_READ_ACCEL()                       WSQ_GPIO_ReadAccInt()                   /*!< return enum 0-1 */
#define BSP_GPIO_READ_BATTERYALERT()                WSQ_GPIO_ReadBatteryAlert()             /*!< return enum 0-1 */
#define BSP_GPIO_READ_RTC_INT()                     WSQ_GPIO_ReadRTCInt()                   /*!< return enum 0-1 */
#define BSP_GPIO_READ_DIGITAL_IN1()                 WSQ_GPIO_ReadDigitalInput1()            /*!< return enum 0-1 */
#define BSP_GPIO_READ_DIGITAL_IN2()                 WSQ_GPIO_ReadDigitalInput2()            /*!< return enum 0-1 */
#define BSP_GPIO_READ_CHG_STATUS()                  WSQ_GPIO_ReadChargingStatus()           /*!< return enum 0-1 */

#define BSP_GPIO_DISPLAY_COLOR_RGB(color)           WSQ_GPIO_DisplayColorRGB(color)  /*!< input arg enum WSQ_Colores_t */
#define BSP_GPIO_ENABLE_OUT_CTL()                   WSQ_GPIO_WriteOutputCtrl(1)
#define BSP_GPIO_DISABLE_OUT_CTL()                  WSQ_GPIO_WriteOutputCtrl(0)
#define BSP_GPIO_WRITE_OUT_CTL(x)					WSQ_GPIO_WriteOutputCtrl(x)

#define BSP_GPIO_ENABLE_SENSORS()                   WSQ_GPIO_EnableSensors(1);\
													BSP_SYSTEM_DELAY(20)
#define BSP_GPIO_DISABLE_SENSORS()                  WSQ_GPIO_EnableSensors(0)

#define BSP_GPIO_ENABLE_ANALOG()                    WSQ_GPIO_EnableAnalog(1);\
													BSP_SYSTEM_DELAY(50)    /*delay for run AOper*/
#define BSP_GPIO_DISABLE_ANALOG()                   WSQ_GPIO_EnableAnalog(0)

/*wIFI*/
#define BSP_WIFI_WRITE_ENABLE                       WSQ_GPIO_WiFiWriteEnable
#define BSP_WIFI_WRITE_RESET(x)                     WSQ_GPIO_WiFiWriteReset(x)		/*input arg 0-1*/
#define BSP_WIFI_ENABLE_COMMAND()                   WSQ_GPIO_WiFiWriteCommandEnable(1)
#define BSP_WIFI_DISABLE_COMMAND()                  WSQ_GPIO_WiFiWriteCommandEnable(0)


/*Sigfox*/
#define BSP_SIGFOX_WRITE_WAKUP                      WSQ_GPIO_SigFoxWriteWakeUp	/*input arg 0-1*/
#define BSP_SIGFOX_WRITE_RESET                      WSQ_GPIO_SigFoxWriteReset	/*input arg 0-1*/


/*gps*/
#define BSP_GPS_WRITE_ENABLE()                           WSQ_GPIO_WiFiWriteEnable(1)
#define BSP_GPS_WRITE_DISABLE()                          WSQ_GPIO_WiFiWriteEnable(0)
#define BSP_GPS_WRITE_RESET(x)                           WSQ_GPIO_WiFiWriteReset(x)	/*input arg 0-1*/
/*end BSP gpio*/



/*begin BSP system*/
typedef WSQ_WakeUp_Source_t							BSP_WakeUp_Source_t ;

#define BSP_SYSTEM_GET_RESET_CAUSE()				((WSQ_WakeUp_Source_t)WSQ_SYSTEM_GetResetCause())
#define BSP_SYSTEM_CORE_SLEEP()                     WSQ_SYSTEM_StandbyCore()
#define BSP_SYSTEM_DELAY(ms)                        WSQ_SYSTEM_Delay(ms)        /*!< delay blocking, input arg milisecond*/
#define BSP_SYSTEM_RESET_SFT()						WSQ_SYSTEM_ResetSFT()

/*Input arg  void (*UART_SigFoxCustomInputHandler)(char)
             void (*UART_WiFiCustomInputHandler)(char)
             void (*VPC_CallbackRxFcn_t)(uint8_t* , uint32_t)
             */
#define BSP_SYSTEM_LL_INIT(CustomCallbackSigfox,\
                           CustomCallbackWifi,\
                           CustomCallbackUsb)       WSQ_SYSTEM_LowLevelInit(CustomCallbackSigfox ,CustomCallbackWifi ,CustomCallbackUsb)

#define BSP_SYSTEM_CLOCK_INIT()                     WSQ_SYSTEM_ClockInit()
#define BSP_SYSTEM_FATAL_EXCEPTION()				WSQ_SYSTEM_FatalException()
#define BSP_SYSTEM_CLEAR_RESET_FLAGS()				LL_RCC_ClearResetFlags()   		/*reset flags system reset RCC_FLAG_PINRST, RCC_FLAG_PORRST, RCC_FLAG_SFTRST, RCC_FLAG_OBLRST, RCC_FLAG_IWDGRST, RCC_FLAG_WWDGRST, RCC_FLAG_LPWRRST*/
#define BSP_SYSTEM_CLEAR_FLAG_WU()					LL_PWR_ClearFlag_WU()
#define BSP_SYSTEM_CLEAR_FLAG_WUT()					LL_RTC_ClearFlag_WUT(RTC)



/*end BSP system*/



/*begin BSP ADC*/
#define BSP_ADC_UPDATE_ANALOG()						 WSQ_ADC_UpdateAnalog()
#define BSP_ADC_READ_SINGLE_CHN(channel)             WSQ_ADC_ReadSingleChannel(channel)  /*return 0-4095 */
#define BSP_ADC_GET_AIN1()                           WSQ_ADC_GetAIN1()
#define BSP_ADC_GET_AIN2()                           WSQ_ADC_GetAIN2()
/*end BSP ADC*/



/*begin BSP uart*/
#define BSP_UART_DEBUG_PUTC                           WSQ_UART_DebugPutChar           /*void (*func_t)(void * , const char)*/
#define BSP_UART_DEBUG_PUTS(s)                        WSQ_UART_DebugPutString(s)

#define BSP_UART_SIGFOX_PUTC                         WSQ_UART_SigFoxPutChar         /*void (*func_t)(void * , const char)*/
#define BSP_UART_SIGFOX_PUTS(s)                      WSQ_UART_SigFoxPutString(s)

#define BSP_UART_WIFI_PUTC                           WSQ_UART_WiFiPutChar           /*void (*func_t)(void * , const char)*/
#define BSP_UART_WIFI_PUTS(s)                        WSQ_UART_WiFiPutString(s)

#define BSP_UART_GPS_PUTC                           //WSQ_UART_GPSPutChar
#define BSP_UART_GPS_PUTS(s)                        //WSQ_UART_GPSPutString(s)
/*end BSP uart*/



/*begin BSP vpc*/
#define BSP_USB_PUTC                                WSQ_VPC_PutChar                 /*void (*func_t)(void * , char)*/
#define BSP_USB_PUTS(msg)                           WSQ_VCP_Print(msg)
#define BSP_USB_STATE_CONFIGURED()					( (hUsbDeviceFS.dev_state) == (USBD_STATE_CONFIGURED)) ? 1 : 0

/*end BSP vpc*/


/*begin BSP rtc*/
#define BSP_RTC_CLEARWAKUP_FLAG()                   WSQ_RTC_ClearWkupFlag()
#define BSP_RTC_SET_TIME(H,M,S,rewrite)                     WSQ_RTC_SetTime(H,M,S,rewrite)
/*end BSP rtc*/


/*begin BSP I2C*/

#define BSP_I2C_TRANSMIT                            WSQ_I2C_Transmit		/*Wrapper*/
#define BSP_I2C_RECEIVE                             WSQ_I2C_Receive			/*Wrapper*/
/*end BSP I2C*/


/*begin BSP FLASH*/
/*write only word*/
#define BSP_FLASH_RESTORE(address,amount)           WSQ_RestoreDataFlash(address ,amount)
#define BSP_FLASH_WRITE(Addr,pData,n)      			WSQ_Flash_Write(Addr,pData,n)
#define BSP_FLASH_READ(Addr,pData ,n)	            WSQ_Flash_Read(Addr,pData ,n)
#define BSP_FLASH_ISEMPTY(Addr,n,IsEmptyZero)		WSQ_Flash_IsEmpty(Addr , n,IsEmptyZero)
#define BSP_FLASH_INIT_ADDR_RESERVED_DATA_CONF		WSQ_INIT_ADDR_RESERVED_DATA_CONFIG		/*address init of flash memory*/
/*end BSP FLASH*/

/*begin BSP high level*/
#ifdef  _MAX17048_
#define BSP_FUEL_GAUGE_GET_SOC()								MAX1708_SOC_Int(&MAX17048)
#define BSP_FUEL_GAUGE_GET_VOLT()								MAX17048_Voltage(&MAX17048)
#define BSP_FUEL_GAUGE_INIT(i2c_transmit ,\
							i2c_receive) 	    					MAX17048_Init(&MAX17048, i2c_transmit, i2c_receive, MAX17048_ADDR_SLAVE);\
																	MAX17048_Compensation(&MAX17048, MAX17048_RCOMP0);\
																	MAX17048_SleepEnable(&MAX17048);\
																	MAX17048_Sleep(&MAX17048, 0);\
																	MAX17048_QStart(&MAX17048)
#define BSP_FUEL_GAUGE_SLEEP()										MAX17048_Sleep(&MAX17048, 0)
#endif

#ifdef  _LC709203F_

#endif

#define BSP_SENSOR_TH_INIT(	i2c_transmit ,\
							i2c_receive) 							SHT30_Init(&SHT30, i2c_transmit, i2c_receive, SHT30_ADDR_SLAVE)

#define BSP_SENSOR_TH_READ_DATA()								    SHT30_ReadData(&SHT30)

#define BSP_SENSOR_AXL_INIT()										LIS2DTW12_Init(&LIS2DTW12, BSP_I2C_TRANSMIT ,BSP_I2C_RECEIVE, LIS2DTW12_ADDRESS);\
																	LIS2DTW12_Active_Mode(&LIS2DTW12,ODR_50HZ);\
																	LIS2DTW12_Update_BDU(&LIS2DTW12, 1)

#define BSP_SENSOR_AXL_READ_AXIS()									LIS2DTW12_Read_AxisXYZ(&LIS2DTW12)
#define BSP_SENSOR_AXL_GET_TILTS_XY()								Axl_Get_Tilts_Pitch_Roll(&AxlDat)  //
#define BSP_SENSOR_AXL_GET_PITCH()									AxlDat.pitch
#define BSP_SENSOR_AXL_GET_ROLL() 									AxlDat.roll
#define BSP_SENSOR_AXL_GET_VIBRATION() 								AxlDat.vibration
#define BSP_SENSOR_AXL_GET_AXIS_GX()								LIS2DTW12_Get_Axis_gX(&LIS2DTW12)
#define BSP_SENSOR_AXL_GET_AXIS_GY()								LIS2DTW12_Get_Axis_gY(&LIS2DTW12)
#define BSP_SENSOR_AXL_GET_AXIS_GZ()								LIS2DTW12_Get_Axis_gZ(&LIS2DTW12)
#define BSP_SENSOR_AXL_POWER_DOWN()	 								LIS2DTW12_PowerDown_Mode(&LIS2DTW12)
#define BSP_SENSOR_AXL_GET_WHO_AM_I()								LIS2DTW12_Who_Am_I(&LIS2DTW12)
/*end BSP high level*/

#define BSP_GPS_LED_ENABLE()						BSP_GPIO_DISPLAY_COLOR_RGB(WSQ_RGB_WHITE)
#define BSP_GPS_LED_DISABLE()						BSP_GPIO_DISPLAY_COLOR_RGB(WSQ_RGB_BLACK)
#define BSP_GPS_LED_TOGGLE()                        //GPIO_PTA0(FALSE)

#endif





#endif /* SOURCE_BSP_BSP_REMAPPING_H_ */
