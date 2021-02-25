/*
 * Configurator_data.h
 *
 *  Created on: Sep 14, 2020
 *      Author: Julian
 */

#ifndef SOURCE_APP_DATA_COFIGURATOR_H_
#define SOURCE_APP_DATA_COFIGURATOR_H_

#include <stdint.h>
#include <bsp_remapping.h>



/**
 * @brief Structure to hold the application config variables.
 */

/*!< common struct*/
typedef struct{
    float ThresholdHigh;
    float ThresholdLow;
    uint8_t IsActive;
}AppDataCfg_t;

/*!< accelerometer data*/
typedef struct{
    uint16_t low,med,high;
    uint8_t IsActive;
}AppDataCfg_axlVibration_t;

typedef struct {
	AppDataCfg_axlVibration_t vibration;
    struct {
		AppDataCfg_t x,y;
		uint8_t IsActive;
    }inclination;
    uint8_t IsActive;
}AppDataCfg_axl_t;

typedef struct {
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
}AppDataCfg_time_t;

typedef enum {
    APPDATACFG_DI_DISABLE,APPDATACFG_DI_RISING,APPDATACFG_DI_FALLING,APPDATACFG_DI_BOTH
}AppDataCfg_DiMode_t;

typedef WSQ_ColorRGB ColorRGB;

/*!< data config struct*/

typedef struct {
	AppDataCfg_t adc1,adc2;
	AppDataCfg_t temperature,humidity;
	AppDataCfg_t airquality;
    uint8_t LowBattSoc;   /*!<minimun  %soc*/
    uint8_t GPS_LocIsActive;
    uint8_t WIFI_LocIsActive;
    uint8_t alwaysSendReportIsActive;
    uint8_t redundanciaIsActive;
    uint8_t downlinkIsActive;
    AppDataCfg_axl_t accelerometer;
    AppDataCfg_time_t time;
    uint8_t keepAlive;
    AppDataCfg_DiMode_t DI_1,DI_2;
    int RCZ;       /*!< sigfox zone*/
    ColorRGB Pulsation_1 , Pulsation_2,Pulsation_3 , Pulsation_Cancel;
    uint8_t NumPulsation;
    uint8_t onlySendLocation;     /*skip frame sensor*/
    char Id_module[12] ; /*id -> 003FD695\0*/
    char Pac_module[20] ; /*id -> 023100144926C529\0*/
    uint8_t idDevice;
    uint8_t DoCtrl;
    uint16_t LowBattmV;
}AppDataCfg_all_t;



/*
 * assert_MODULOX(readflash()) datos buenos en flash o datos por defecto
 *
 * | --COMANDO--         				| --RESPUESTA--  |  	--MODULO--
 * | AT+comando1=1,max,min   	 		|	ok    	 	 |		(adc1 ,adc2 ,temperature,humidity ,airquality)
 * | AT+comando2=(u8)   		 		|	ok		 	 |		(LowBattSoc ,NumPulsation, RCZ,keepAlive , DI_1,DI_2 ,Pulsation_1 , Pulsation_2,Pulsation_3 , Pulsation_Cancel)
 * | AT+comando3=flagEnable(1 | 0)  	|	ok  	 	 |		(GPS_LocIsActive,WIFI_LocIsActive,alwaysSendReportIsActive,downlinkIsActive )
 * | AT+comando4=1,low,med,high or TDB  | 	ok     	 	 |		(aceelerometer)
 * | AT+comando5=h,m,s
 * 	 AT+comando6		 	    		|	ok		 	 |	SAVE

 	 writeflash
 	 reinicie cuando desconecte
 * */




#endif /* SOURCE_APP_DATA_COFIGURATOR_H_ */
