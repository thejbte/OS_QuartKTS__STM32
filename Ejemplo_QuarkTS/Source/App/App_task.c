/*
 * App.c
 *
 *  Created on: 10/09/2020
 *      Author: Julian
 */

#include "App.h"
#include <stddef.h>
/* ↑offsetof  -> #define f(st, m) \
								((size_t) ( (char *)&((st *)(0))->m - (char *)0 ))*/


uint32_t	CounterKeepAlive = 0 ;
//idDevice = 0;  /*add new*/
static int8_t App_AnyThresholdsReached(void);
static void   App_UpdateReportData(void);

AppDataCfg_all_t AppData_Config = {.DI_1 = 0,
		.DI_2 = 0,
		.GPS_LocIsActive = 0,
		.LowBattSoc = 20,
		.NumPulsation = 0,
		.Pulsation_1.rgb = COLOR_RGB_YELLOW,
		.Pulsation_2.rgb = COLOR_RGB_AQUA,
		.Pulsation_3.rgb = COLOR_RGB_RED,
		.Pulsation_Cancel.rgb = COLOR_RGB_FUCHSIA,
		.RCZ = WSSFM1XRX_RCZ4,
		.WIFI_LocIsActive = 0,
		.accelerometer.IsActive = 0,
		.accelerometer.inclination.IsActive = 0,
		.accelerometer.inclination.x.ThresholdLow = 0,
		.accelerometer.inclination.x.ThresholdHigh = 360,
		.accelerometer.inclination.y.ThresholdLow = 0,
		.accelerometer.inclination.y.ThresholdHigh = 360,
		.accelerometer.vibration.IsActive = 0,
		.accelerometer.vibration.low = 10,// max 20 muy fuerte
		.accelerometer.vibration.med = 0,
		.accelerometer.vibration.high= 0,
		.adc1.IsActive = 0,
		.adc1.ThresholdLow = 0,
		.adc1.ThresholdHigh = 0,
		.adc2.IsActive = 0,
		.adc2.ThresholdLow = 0,
		.adc2.ThresholdHigh = 0,
		.airquality.IsActive = 0,
		.airquality.ThresholdLow = 0,
		.airquality.ThresholdHigh = 0,
		.alwaysSendReportIsActive = 0,
		.downlinkIsActive = 0,
		.humidity.IsActive = 0,
		.humidity.ThresholdLow = 0,
		.humidity.ThresholdHigh = 0,

		.temperature.IsActive = 0,
		.temperature.ThresholdLow = 0,
		.temperature.ThresholdHigh = 0,
		.keepAlive = 0,
		.redundanciaIsActive = 0,
		.time.hour = 1,
		.time.min = 0,
		.time.sec = 0,
		.onlySendLocation = 0,
		.Id_module = {0},
		.Pac_module = {0},
		.idDevice = APP_ID_DEVICE_WSQ,
		.DoCtrl = 0
};

AppDataUp_Frame_t Isquare_Data ; 	/*data sigfox to send*/

qTask_t TaskApplicationFSM;
qTask_t TaskHandlerEvents_Scan;
qSM_t   ApplicationFSM;

BSP_WakeUp_Source_t WakeUp_Source;


/*===========================================================================================*/
void App_Task_ScanAndEvents_Callback(qEvent_t arg){
	static BSP_WakeUp_Source_t WakeUp={.Source=WKUP_UNKNOW};


	static uint8_t ShouldReport =0 ;
	static uint8_t ShouldReportISQC = 0;

	qCR_Begin{
		WakeUp.Source = (int)arg->TaskData;

		App_Update_BattSocOrmV();
		App_UpdateReportData();

		BSP_SENSOR_TH_READ_DATA();
		for( int i = 0; i< 2 ; i++){
				BSP_SENSOR_TH_READ_DATA();
				qDebug_Float(SHT30.temperature); /*GetTemp*/
				qDebug_Float(SHT30.humidity ); /*Gethum*/
		}

		switch( WakeUp.Source){
		case WKUP_TIME:
			(void)App_AnyThresholdsReached();
			if(	AppData_Config.NumPulsation != 0 ){
				ShouldReportISQC = 1;
			}else {
				ShouldReport = 1;
			}

			break;
		case 	WKUP_PIN:

			ShouldReport = 1;
			break;
		default:  /*others pulsations 1,2,3*/
			ShouldReportISQC = 1;
			ShouldReport = 0;
			break;
		}

		if(1 == Isquare_Data.Sensors.id.LowBattery )
			qDebug_Decimal(Isquare_Data.Sensors.id.LowBattery);

		if(ShouldReport  || ShouldReportISQC )
		{
			/* TODO : Set iddevice APP_ID_DEVICE_ISMC_MOBILITY ATCLI
			 * */

			Service_Sigfox_Run(1);
			qCR_WaitUntil(Service_Sigfox_GetStatus() == WSSFM1XRX_STATUS_MODULE_INITIALIZED);

			if ( 0 == AppData_Config.onlySendLocation   )   /*skip frame sensors with onlysendframe*/
			{
				qTrace_Message("sensors\r\n");
				/*in keep alive transmit all sensors*/
				Isquare_Data.Sensors.id.type =  APPDATAUP_SENSORS;
				Service_Sigfox_Send(Isquare_Data.AllBytes, AppData_Config.downlinkIsActive);
				qCR_WaitUntil(Service_Sigfox_GetStatus()==WSSFM1XRX_STATUS_SENT_MESSAGE);
				if( AppData_Config.downlinkIsActive){
					if(1 == Service_Sigfox_GetDownlinkStatus())
						App_DiscrimateFrameDownlink(Service_Sigfox_GetDownlinkFrame());
					AppData_Config.downlinkIsActive = 0; /*clear downlink (the wakeup read memory flash egain)*/
					//Service_Gps_SetDonwlink(AppData_Config.downlinkIsActive);
				}
			}
		}

		BSP_GPIO_WRITE_OUT_CTL(AppData_Config.DoCtrl);
		qCR_WaitUntil(Service_Sigfox_QueueIsEmpty());
		qTask_Notification_Send(&TaskApplicationFSM, (void*)OPERATION_SLEEP) ;
		qTask_Set_State(qTask_Self(),qDisabled);
		qCR_Yield;
	}qCR_End;
}


/*===========================================================================================*/
static void App_UpdateReportData(void){

}

/*===========================================================================================*/
/** Return -1 if not thresholds reached, 1 if Thresholds reached*/
static int8_t App_AnyThresholdsReached(void){
	int8_t AnyThresholdIsReady =
			(Isquare_Data.Sensors.sen_bf.adc1 < AppData_Config.adc1.ThresholdLow || Isquare_Data.Sensors.sen_bf.adc1 > AppData_Config.adc1.ThresholdHigh )							||
			(Isquare_Data.Sensors.sen_bf.adc2 < AppData_Config.adc2.ThresholdLow || Isquare_Data.Sensors.sen_bf.adc2 > AppData_Config.adc2.ThresholdHigh )							||
			(Isquare_Data.Sensors.sen_bf.AirQuality < AppData_Config.airquality.ThresholdLow || Isquare_Data.Sensors.sen_bf.AirQuality > AppData_Config.airquality.ThresholdHigh )	||
			(Isquare_Data.Sensors.sen_bf.hum < AppData_Config.humidity.ThresholdLow || Isquare_Data.Sensors.sen_bf.hum > AppData_Config.humidity.ThresholdHigh )						||
			(Isquare_Data.Sensors.sen_bf.temp < AppData_Config.temperature.ThresholdLow || Isquare_Data.Sensors.sen_bf.temp > AppData_Config.temperature.ThresholdHigh )				||
			(Isquare_Data.Sensors.id.LowBattery == 1)																										||
			(Isquare_Data.Sensors.sen_bf.pitch < AppData_Config.accelerometer.inclination.x.ThresholdLow || Isquare_Data.Sensors.sen_bf.pitch >AppData_Config.accelerometer.inclination.x.ThresholdHigh   )	||
			(Isquare_Data.Sensors.sen_bf.roll < AppData_Config.accelerometer.inclination.y.ThresholdLow || Isquare_Data.Sensors.sen_bf.roll >AppData_Config.accelerometer.inclination.y.ThresholdHigh   ) ||
			(Isquare_Data.Sensors.sen_bf.dummy >= AppData_Config.accelerometer.vibration.low   )	; //no use med and high

	return AnyThresholdIsReady;
}

/*===========================================================================================*/

void App_Task_Idle(qEvent_t e){
	//WSQ_SYSTEM_FeedCOP();/*TODO: WDT new*/
}



/**
 * @brief Discriminate Frame Downlink.
 * @param NumericFrame structure the SigFox data;
 */


uint8_t App_DiscrimateFrameDownlink(uint8_t *NumericFrame){

	return 1;
}

void App_Update_BattSocOrmV(void){

}
