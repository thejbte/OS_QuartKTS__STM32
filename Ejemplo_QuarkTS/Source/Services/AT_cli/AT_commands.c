/**
 * @file AT_commands.c
 * @brief interface Command line AT
 * @date Mar 3, 2020
 * @author Esp.Ing.Julian Bustamante N
 */

/*TODO: agregar READ responce state... */
#include "../AT_cli/AT_commands.h"

#include <stdio.h>
//#include <gpsinfo_lite.h>
//#include <Task_Service_gps.h>
#include <bsp_remapping.h>
#include <Task_Service_Sigfox.h>

#include "data_cofigurator.h"  // para AppDataCfg_all_t
#include "App.h"

char StrReportTime[20];
const char *StrIdDevice[7] ={
	"WSQ " ,
	"GSQ "

};
/*EXTERN DATA*/

extern AppDataCfg_all_t AppData_Config;
extern uint32_t	CounterKeepAlive ;
extern qTask_t TaskApplicationFSM;

/*Definitions*/
static qTask_t Task_ATParser;
static qATCLI_t ATCommandParser;

static char ParserInput[AT_CLI_MAX_INPUT_BUFF_SIZE];  /** Buffer parser input CLI AT*/
static char ParserOutput[AT_CLI_MAX_OUTPUT_BUFF_SIZE]; /** Buffer parser output CLI AT*/


/*Commands*/
static qATCLI_Command_t AT_HELP,
						AT_PAC,
						AT_ID,
						AT_BATT,
						AT_ADC,
						AT_DI,
						AT_TIME,
						AT_HT,
						AT_AQ,
						AT_GPS,
						AT_WIFI,
						AT_AR,
						AT_DL,
						AT_PULS,
						AT_RCZ,
						AT_ACCEL,
						AT_REDUND,


						AT_APIINFO,
						AT_RESETFACT,
						AT_SAVE,
						AT_READ,
						AT_ONLY_SF,
						AT_ID_DEV,
						AT_DOCTRL;
						/*AT_SLEEP,
						AT_REBOOT,
						AT_GET_GPS_FRAME,
						AT_DEBUG_GPS_CONTINUOUS,
						AT_SOURCE_WKUP, //AT_APIVER AT_EXIT*/


#define STATIC static


STATIC qATCLI_Response_t AT_Callback_Help( qATCLI_Handler_t parser, qATCLI_PreCmd_t param);
STATIC qATCLI_Response_t AT_Callback_Pac( qATCLI_Handler_t parser, qATCLI_PreCmd_t param);
STATIC qATCLI_Response_t AT_Callback_Id( qATCLI_Handler_t parser, qATCLI_PreCmd_t param);


STATIC qATCLI_Response_t AT_Callback_Batt( qATCLI_Handler_t parser, qATCLI_PreCmd_t param);
STATIC qATCLI_Response_t AT_Callback_Adc( qATCLI_Handler_t parser, qATCLI_PreCmd_t param);
STATIC qATCLI_Response_t AT_Callback_Di( qATCLI_Handler_t parser, qATCLI_PreCmd_t param);
STATIC qATCLI_Response_t AT_Callback_Time( qATCLI_Handler_t parser, qATCLI_PreCmd_t param);
STATIC qATCLI_Response_t AT_Callback_Hum_Temp( qATCLI_Handler_t parser, qATCLI_PreCmd_t param);
STATIC qATCLI_Response_t AT_Callback_AirQ( qATCLI_Handler_t parser, qATCLI_PreCmd_t param);
STATIC qATCLI_Response_t AT_Callback_Gps( qATCLI_Handler_t parser, qATCLI_PreCmd_t param);
STATIC qATCLI_Response_t AT_Callback_WiFi( qATCLI_Handler_t parser, qATCLI_PreCmd_t param);
STATIC qATCLI_Response_t AT_Callback_OnlySendLocation( qATCLI_Handler_t parser, qATCLI_PreCmd_t param);
STATIC qATCLI_Response_t AT_Callback_AlwaysReport( qATCLI_Handler_t parser, qATCLI_PreCmd_t param);
STATIC qATCLI_Response_t AT_Callback_Downlink( qATCLI_Handler_t parser, qATCLI_PreCmd_t param);
STATIC qATCLI_Response_t AT_Callback_Pulsation( qATCLI_Handler_t parser, qATCLI_PreCmd_t param);
STATIC qATCLI_Response_t AT_Callback_Rcz( qATCLI_Handler_t parser, qATCLI_PreCmd_t param);
STATIC qATCLI_Response_t AT_Callback_Accelerometer( qATCLI_Handler_t parser, qATCLI_PreCmd_t param);
STATIC qATCLI_Response_t AT_Callback_ApiInfo( qATCLI_Handler_t parser, qATCLI_PreCmd_t param);
STATIC qATCLI_Response_t AT_Callback_RepeatPayload( qATCLI_Handler_t parser, qATCLI_PreCmd_t param);
STATIC qATCLI_Response_t AT_Callback_Read( qATCLI_Handler_t parser, qATCLI_PreCmd_t param);
STATIC qATCLI_Response_t AT_Callback_IdDevice( qATCLI_Handler_t parser, qATCLI_PreCmd_t param);
STATIC qATCLI_Response_t AT_Callback_DoCtrl( qATCLI_Handler_t parser, qATCLI_PreCmd_t param);






STATIC qATCLI_Response_t AT_Callback_ResetFactory( qATCLI_Handler_t parser, qATCLI_PreCmd_t param);
STATIC qATCLI_Response_t AT_Callback_Save( qATCLI_Handler_t parser, qATCLI_PreCmd_t param);

/**
 * @brief This function subscribe command AT
 */
void AT_Command_Init(void){
	qATCLI_Setup( &ATCommandParser, BSP_USB_PUTC,
			ParserInput, sizeof(ParserInput), ParserOutput, sizeof(ParserOutput),
			"Hub " __DATE__ " " __TIME__, "OK", "ERROR", "UNKNOWN", "\r\n");
	qATCLI_CmdSubscribe( &ATCommandParser, &AT_HELP, "at+help", AT_Callback_Help, QATCLI_CMDTYPE_ACT, "Show the available commands");
	//qATCLI_CmdSubscribe( &ATCommandParser, &AT_APIINFO, "at+apiinfo", AT_APIINFO_Callback, QATCLI_CMDTYPE_ACT | QATCLI_CMDTYPE_READ, "Get the API information" );

	qATCLI_CmdSubscribe( &ATCommandParser, &AT_PAC,   AT_CMD_STR_PAC    ,AT_Callback_Pac, QATCLI_CMDTYPE_ACT | QATCLI_CMDTYPE_READ | QATCLI_CMDTYPE_TEST, "Get the node initial PAC" );
	qATCLI_CmdSubscribe( &ATCommandParser, &AT_ID,    AT_CMD_STR_ID     , AT_Callback_Id, QATCLI_CMDTYPE_ACT | QATCLI_CMDTYPE_READ | QATCLI_CMDTYPE_TEST, "Get the node SigFox ID" );
	qATCLI_CmdSubscribe( &ATCommandParser, &AT_BATT,  AT_CMD_STR_BATT   ,AT_Callback_Batt, QATCLI_CMDTYPE_ACT | QATCLI_CMDTYPE_READ | QATCLI_CMDTYPE_TEST | QATCLI_CMDTYPE_PARA | 0x22, "Battery parameters" );
	qATCLI_CmdSubscribe( &ATCommandParser, &AT_ADC,   AT_CMD_STR_ADC    , AT_Callback_Adc, QATCLI_CMDTYPE_ACT | QATCLI_CMDTYPE_READ | QATCLI_CMDTYPE_TEST | QATCLI_CMDTYPE_PARA | 0x44, " Set ADC");
	qATCLI_CmdSubscribe( &ATCommandParser, &AT_DI,    AT_CMD_STR_DI    , AT_Callback_Di, QATCLI_CMDTYPE_ACT | QATCLI_CMDTYPE_READ | QATCLI_CMDTYPE_TEST | QATCLI_CMDTYPE_PARA | 0x22, "Digital input ");
	qATCLI_CmdSubscribe( &ATCommandParser, &AT_TIME,  AT_CMD_STR_TIME   , AT_Callback_Time, QATCLI_CMDTYPE_ACT | QATCLI_CMDTYPE_READ | QATCLI_CMDTYPE_TEST | QATCLI_CMDTYPE_PARA | 0x44, "Change time report and kepp alive"); /*at+time? at+time=10,5*/
	qATCLI_CmdSubscribe( &ATCommandParser, &AT_HT,    AT_CMD_STR_HT     , AT_Callback_Hum_Temp, QATCLI_CMDTYPE_ACT | QATCLI_CMDTYPE_READ | QATCLI_CMDTYPE_TEST | QATCLI_CMDTYPE_PARA | 0x44, " Temperature and humidity");
	qATCLI_CmdSubscribe( &ATCommandParser, &AT_AQ,    AT_CMD_STR_AIRQ   , AT_Callback_AirQ, QATCLI_CMDTYPE_ACT | QATCLI_CMDTYPE_READ | QATCLI_CMDTYPE_TEST | QATCLI_CMDTYPE_PARA | 0x33, " Airquality");
	qATCLI_CmdSubscribe( &ATCommandParser, &AT_GPS,   AT_CMD_STR_GPS    , AT_Callback_Gps, QATCLI_CMDTYPE_ACT | QATCLI_CMDTYPE_READ | QATCLI_CMDTYPE_TEST | QATCLI_CMDTYPE_PARA | 0x11, " Gps");
	qATCLI_CmdSubscribe( &ATCommandParser, &AT_WIFI,  AT_CMD_STR_WIFI   , AT_Callback_WiFi, QATCLI_CMDTYPE_ACT | QATCLI_CMDTYPE_READ | QATCLI_CMDTYPE_TEST | QATCLI_CMDTYPE_PARA | 0x11, " Wi-Fi");
	qATCLI_CmdSubscribe( &ATCommandParser, &AT_AR,    AT_CMD_STR_ALWAYS , AT_Callback_AlwaysReport, QATCLI_CMDTYPE_ACT | QATCLI_CMDTYPE_READ | QATCLI_CMDTYPE_TEST | QATCLI_CMDTYPE_PARA | 0x11, " always report");
	qATCLI_CmdSubscribe( &ATCommandParser, &AT_DL,    AT_CMD_STR_DL     , AT_Callback_Downlink, QATCLI_CMDTYPE_ACT | QATCLI_CMDTYPE_READ | QATCLI_CMDTYPE_TEST | QATCLI_CMDTYPE_PARA | 0x11, "downlink");
	qATCLI_CmdSubscribe( &ATCommandParser, &AT_PULS,  AT_CMD_STR_PULSED , AT_Callback_Pulsation, QATCLI_CMDTYPE_ACT | QATCLI_CMDTYPE_READ | QATCLI_CMDTYPE_TEST | QATCLI_CMDTYPE_PARA | 0x55, " NPulsation and color by event");
	qATCLI_CmdSubscribe( &ATCommandParser, &AT_RCZ,   AT_CMD_STR_RCZ    , AT_Callback_Rcz, QATCLI_CMDTYPE_ACT | QATCLI_CMDTYPE_READ | QATCLI_CMDTYPE_TEST | QATCLI_CMDTYPE_PARA | 0x11, " change frequency sigfox");
	qATCLI_CmdSubscribe( &ATCommandParser, &AT_ACCEL, AT_CMD_STR_AXL    , AT_Callback_Accelerometer, QATCLI_CMDTYPE_ACT | QATCLI_CMDTYPE_READ | QATCLI_CMDTYPE_TEST | QATCLI_CMDTYPE_PARA | 0x74, " accelerometer");
	qATCLI_CmdSubscribe( &ATCommandParser, &AT_APIINFO,AT_CMD_STR_INFO  , AT_Callback_ApiInfo , QATCLI_CMDTYPE_ACT | QATCLI_CMDTYPE_READ | QATCLI_CMDTYPE_TEST, "Get api info" );
	qATCLI_CmdSubscribe( &ATCommandParser, &AT_REDUND,AT_CMD_STR_REPEAT , AT_Callback_RepeatPayload, QATCLI_CMDTYPE_ACT | QATCLI_CMDTYPE_READ | QATCLI_CMDTYPE_TEST | QATCLI_CMDTYPE_PARA | 0x11, "redundancia");
	qATCLI_CmdSubscribe( &ATCommandParser, &AT_READ,  AT_CMD_STR_READ   , AT_Callback_Read, QATCLI_CMDTYPE_ACT | QATCLI_CMDTYPE_READ | QATCLI_CMDTYPE_TEST | QATCLI_CMDTYPE_PARA | 0x11 , "read all parameters" );
	qATCLI_CmdSubscribe( &ATCommandParser, &AT_ONLY_SF,AT_CMD_STR_ONLYLOC, AT_Callback_OnlySendLocation, QATCLI_CMDTYPE_ACT | QATCLI_CMDTYPE_READ | QATCLI_CMDTYPE_TEST | QATCLI_CMDTYPE_PARA | 0x11, " only send frame");
	qATCLI_CmdSubscribe( &ATCommandParser, &AT_ID_DEV,AT_CMD_STR_IDEV   , AT_Callback_IdDevice, QATCLI_CMDTYPE_ACT | QATCLI_CMDTYPE_READ | QATCLI_CMDTYPE_TEST | QATCLI_CMDTYPE_PARA | 0x11, " id device");
	qATCLI_CmdSubscribe( &ATCommandParser, &AT_DOCTRL,AT_CMD_STR_GPO    , AT_Callback_DoCtrl, QATCLI_CMDTYPE_ACT | QATCLI_CMDTYPE_READ | QATCLI_CMDTYPE_TEST | QATCLI_CMDTYPE_PARA | 0x11, " digital output");



	qATCLI_CmdSubscribe( &ATCommandParser, &AT_RESETFACT, AT_CMD_STR_RESETF , AT_Callback_ResetFactory, QATCLI_CMDTYPE_ACT |QATCLI_CMDTYPE_TEST, "Reset factory");
	qATCLI_CmdSubscribe( &ATCommandParser, &AT_SAVE, AT_CMD_STR_SAVE , AT_Callback_Save, QATCLI_CMDTYPE_ACT | QATCLI_CMDTYPE_TEST, "Save config");

	qOS_Add_ATCLITask( &Task_ATParser, &ATCommandParser, qLowest_Priority );
}


/*============================================================================*/
/**
 *@brief Show the available commands
 *@test at+help?
 */
static qATCLI_Response_t AT_Callback_Help( qATCLI_Handler_t parser, qATCLI_PreCmd_t param){
	qATCLI_Command_t *Command;
	char buf[70];
	qATCLI_CmdIterate(&ATCommandParser, qTrue);
	parser->puts("*****************************************************************\r\n");
	parser->puts("|                     AT Command Line                           |\r\n");
	parser->puts("-----------------------------------------------------------------\r\n");
	sprintf(buf,"| %-12s | %-46s |\r\n","Command","Function");
	parser->puts(buf);
	parser->puts("-----------------------------------------------------------------\r\n");
	while ( NULL != ( Command = qATCLI_CmdIterate( &ATCommandParser, qFalse ) ) ){
		sprintf(parser->Output,"| %-12s | %-46s |\r\n", Command->Text, (char*)Command->param);
		parser->puts(parser->Output);
	}
	parser->puts("-----------------------------------------------------------------\r\n");
	parser->Output[0] = '\0' ;
	return QATCLI_OK;
}

/*============================================================================*/

/**
 *@brief Get the node initial PAC
 *@test at+pac?
 *@return pac string
 * */
static qATCLI_Response_t AT_Callback_Pac( qATCLI_Handler_t parser, qATCLI_PreCmd_t param){
	qATCLI_Response_t RetValue = QATCLI_ERROR;

	switch( param->Type ){
	case QATCLI_CMDTYPE_ACT: /*< AT+cmd */
		//RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_READ: /*< AT+cmd? */
		sprintf(parser->Output,"%s\r\n",AppData_Config.Pac_module);
		RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_TEST:
		sprintf(parser->Output,"%s","16 digits size");
		RetValue = QATCLI_OK;
		break;
	default : break;
	}
	return RetValue;
}

/*============================================================================*/

/**
 *@brief Get the node SigFox ID
 *@test at+id?
 *@return id string
 * */
static qATCLI_Response_t AT_Callback_Id( qATCLI_Handler_t parser, qATCLI_PreCmd_t param){
	qATCLI_Response_t RetValue = QATCLI_ERROR;

	switch( param->Type ){
	case QATCLI_CMDTYPE_ACT: /*< AT+cmd */
		//RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_READ: /*< AT+cmd? */
		sprintf(parser->Output,"%s\r\n",AppData_Config.Id_module);
		RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_TEST:
		sprintf(parser->Output,"%s","8 digits size");
		RetValue = QATCLI_OK;
		break;
	default : break;
	}
	return RetValue;
}

/*============================================================================*/

/**
 *@brief Get a battery measurement
 *@test at+batt?
 *@test at+batt=soc,mvolt
 *@return mvolt,soc
 * */
/*   AT+comando2=(u8)   */
static qATCLI_Response_t AT_Callback_Batt( qATCLI_Handler_t parser, qATCLI_PreCmd_t param){
	qATCLI_Response_t RetValue = QATCLI_ERROR;

	switch( param->Type ){
	case QATCLI_CMDTYPE_ACT: /*< AT+cmd */
		//RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_READ: /*< AT+cmd? */
		//sprintf( parser->Output, "%u,%u", BSP_FUEL_GAUGE_GET_VOLT(),BSP_FUEL_GAUGE_GET_SOC() );
		RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_PARA:  //AT+cmd=X,Y
		AppData_Config.LowBattSoc = param->GetArgInt(1) ;
		AppData_Config.LowBattmV = param->GetArgInt(2) ;
		RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_TEST:
		sprintf(parser->Output,"%s%s",AT_CMD_STR_BATT,"=soc[0-100],mvolt[2700-4200]");
		RetValue = QATCLI_OK;
		break;
	default : break;
	}
	return RetValue;
}


/*============================================================================*/
/**
 *@brief set config adc
 *@test AT+ADC=channel,enable ,max,min
 *@note range [0-4095]*/
static qATCLI_Response_t AT_Callback_Adc( qATCLI_Handler_t parser, qATCLI_PreCmd_t param){
	qATCLI_Response_t RetValue = QATCLI_ERROR;

	switch( param->Type ){
	case QATCLI_CMDTYPE_ACT: // AT+cmd
		//RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_READ:
		//DOWNLINK_F = ASSERT_APP_CONFIG_DL(Flash_ReadWord(InitMemoryAddressReserved + OFFSET_ADDR_DL_ATCLI));
		//sprintf(parser->Output,"%s",DOWNLINK_F == APP_DL_TRUE ?"True":"False");
		RetValue = QATCLI_NORESPONSE;
		break;
	case QATCLI_CMDTYPE_PARA:
		if(param->GetArgInt(1) == 1){
			AppData_Config.adc1.IsActive = param->GetArgInt(2) ;
			AppData_Config.adc1.ThresholdHigh  = param->GetArgFlt(3) ;
			AppData_Config.adc1.ThresholdLow = param->GetArgFlt(4) ;
		}else if(param->GetArgInt(1) == 2){
			AppData_Config.adc2.IsActive = param->GetArgInt(2) ;
			AppData_Config.adc2.ThresholdHigh  = param->GetArgFlt(3) ;
			AppData_Config.adc2.ThresholdLow = param->GetArgFlt(4) ;
		}else{
			/*add code*/
		}
		RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_TEST:
		sprintf(parser->Output,"%s%s",AT_CMD_STR_ADC,"=channel[1-2],enable[0-1],max[0-4095],min[0-4095]");
		RetValue = QATCLI_OK;
		break;

	default : break;
	}
	return RetValue;
}

/**
 *@brief set config di
 *@test AT+DI=channel,edge
 *@note edge [0-3]-> APPDATACFG_DI_DISABLE = 0,APPDATACFG_DI_RISING = 1,APPDATACFG_DI_FALLING = 2,APPDATACFG_DI_BOTH = 3
 */
static qATCLI_Response_t AT_Callback_Di( qATCLI_Handler_t parser, qATCLI_PreCmd_t param){
	qATCLI_Response_t RetValue = QATCLI_ERROR;

	switch( param->Type ){
	case QATCLI_CMDTYPE_ACT: // AT+cmd
		//RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_READ:
				RetValue = QATCLI_NORESPONSE;
		break;
	case QATCLI_CMDTYPE_TEST:
		sprintf(parser->Output,"%s%s",AT_CMD_STR_DI,"=channel[1-2],edge[0-3]\nedge:\nAPPDATACFG_DI_DISABLE = 0\nAPPDATACFG_DI_RISING = 1\nAPPDATACFG_DI_FALLING = 2\nAPPDATACFG_DI_BOTH = 3\n");
		RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_PARA:
		if(param->GetArgInt(1) == 1){
				AppData_Config.DI_1  =  (AppDataCfg_DiMode_t)(param->GetArgInt(2) > 3 ? 0 :param->GetArgInt(2));
		}else if(param->GetArgInt(1) == 2){
			AppData_Config.DI_2  =  (AppDataCfg_DiMode_t)(param->GetArgInt(2) > 3 ? 0 :param->GetArgInt(2));
		}else{
			/*add code*/
		}
		RetValue = QATCLI_OK;
		break;

	default : break;
	}
	return RetValue;
}



/**
 *@brief set config time
 *@test AT+TIME=keepalive,hours,minutes,seconds
 *@note keep alive is x times h:m:s
 *@note h:m:s -> [0-17],[0-59],[0-59]
 */
static qATCLI_Response_t AT_Callback_Time( qATCLI_Handler_t parser, qATCLI_PreCmd_t param){
	qATCLI_Response_t RetValue = QATCLI_ERROR;
	switch( param->Type ){
	case QATCLI_CMDTYPE_ACT: // AT+cmd
		//RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_READ:
		sprintf(parser->Output,"%d %02d:%02d:%02d",AppData_Config.keepAlive,AppData_Config.time.hour,AppData_Config.time.min,AppData_Config.time.sec);
		RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_PARA:
		AppData_Config.keepAlive = param->GetArgInt(1);
		AppData_Config.time.hour = param->GetArgInt(2);
		AppData_Config.time.min= param->GetArgInt(3);
		AppData_Config.time.sec = param->GetArgInt(4);

		//nuevo
		BSP_RTC_SET_TIME(AppData_Config.time.hour,AppData_Config.time.min,AppData_Config.time.sec,1) ;
		RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_TEST:
		sprintf(parser->Output,"%s%s",AT_CMD_STR_TIME,"=keepalive[is x times h:m:s],hours[0-17],minutes[0-59],seconds[0-59]");
		RetValue = QATCLI_OK;
		break;

	default : break;
	}
	return RetValue;

}



/*============================================================================*/
/**
 *@brief set config sensor HT
 *@test AT+HT=sel,enable,max,min
 *@note sel -> 1 Humidity   , 2 -> temperature
 *@note range H: 10-90 % , T: -40 to 90
 */
static qATCLI_Response_t AT_Callback_Hum_Temp( qATCLI_Handler_t parser, qATCLI_PreCmd_t param){
	qATCLI_Response_t RetValue = QATCLI_ERROR;

	switch( param->Type ){
	case QATCLI_CMDTYPE_ACT: // AT+cmd
		//RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_READ:
		//DOWNLINK_F = ASSERT_APP_CONFIG_DL(Flash_ReadWord(InitMemoryAddressReserved + OFFSET_ADDR_DL_ATCLI));
		//sprintf(parser->Output,"%s",DOWNLINK_F == APP_DL_TRUE ?"True":"False");
		RetValue = QATCLI_NORESPONSE;
		break;
	case QATCLI_CMDTYPE_PARA:
		AppData_Config.humidity.IsActive = AppData_Config.temperature.IsActive = param->GetArgInt(2);
		if(param->GetArgInt(1) == 1){  /*Humidity*/
			AppData_Config.humidity.ThresholdHigh  = param->GetArgFlt(3) ;
			AppData_Config.humidity.ThresholdLow = param->GetArgFlt(4) ;
		}else if(param->GetArgInt(1) == 2){ /*temperature*/
			AppData_Config.temperature.ThresholdHigh  = param->GetArgFlt(3) ;
			AppData_Config.temperature.ThresholdLow = param->GetArgFlt(4) ;
		}else{
			/*add code*/
		}

		RetValue = QATCLI_OK;
		break;

	case QATCLI_CMDTYPE_TEST:
		sprintf(parser->Output,"%s%s",AT_CMD_STR_HT,"=channel[1->HR - 2->T],enable[0-1],max,min [HR: 10 - 90 T:-40 - 90]");
		RetValue = QATCLI_OK;
		break;
	default : break;
	}
	return RetValue;
}


/*============================================================================*/
/**
 *@brief set config sensor AQ
 *@test AT+AIRQ=enable,max,min
 *@note range
 */
static qATCLI_Response_t AT_Callback_AirQ( qATCLI_Handler_t parser, qATCLI_PreCmd_t param){
	qATCLI_Response_t RetValue = QATCLI_ERROR;

	switch( param->Type ){
	case QATCLI_CMDTYPE_ACT: // AT+cmd
		//RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_READ:

		RetValue = QATCLI_NORESPONSE;
		break;
	case QATCLI_CMDTYPE_PARA:
			AppData_Config.airquality.IsActive = param->GetArgInt(1) ;
			AppData_Config.airquality.ThresholdHigh  = param->GetArgFlt(2) ;
			AppData_Config.airquality.ThresholdLow = param->GetArgFlt(3) ;
		RetValue = QATCLI_OK;
		break;

	case QATCLI_CMDTYPE_TEST:
		sprintf(parser->Output,"%s%s",AT_CMD_STR_AIRQ,"=enable[0-1],max[0-4095],min[0-4095]");
		RetValue = QATCLI_OK;
		break;
	default : break;
	}
	return RetValue;
}



/*============================================================================*/
/**
 *@brief set config GPS
 *@test AT+GPS=enable
 */
static qATCLI_Response_t AT_Callback_Gps( qATCLI_Handler_t parser, qATCLI_PreCmd_t param){
	qATCLI_Response_t RetValue = QATCLI_ERROR;

	switch( param->Type ){
	case QATCLI_CMDTYPE_ACT: // AT+cmd
		//RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_READ:

		RetValue = QATCLI_NORESPONSE;
		break;
	case QATCLI_CMDTYPE_PARA:
			AppData_Config.GPS_LocIsActive = param->GetArgInt(1) ;
		RetValue = QATCLI_OK;
		break;

	case QATCLI_CMDTYPE_TEST:
		sprintf(parser->Output,"%s%s",AT_CMD_STR_GPS,"=enable[0-1]");
		RetValue = QATCLI_OK;
		break;
	default : break;
	}
	return RetValue;
}

/*============================================================================*/
/**
 *@brief set config wifi
 *@test AT+WIFI=enable
 */
static qATCLI_Response_t AT_Callback_WiFi( qATCLI_Handler_t parser, qATCLI_PreCmd_t param){
	qATCLI_Response_t RetValue = QATCLI_ERROR;

	switch( param->Type ){
	case QATCLI_CMDTYPE_ACT: // AT+cmd
		//RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_READ:

		RetValue = QATCLI_NORESPONSE;
		break;
	case QATCLI_CMDTYPE_PARA:
			AppData_Config.WIFI_LocIsActive = param->GetArgInt(1) ;
		RetValue = QATCLI_OK;
		break;

	case QATCLI_CMDTYPE_TEST:
		sprintf(parser->Output,"%s%s",AT_CMD_STR_WIFI,"=enable[0-1]");
		RetValue = QATCLI_OK;
		break;
	default : break;
	}
	return RetValue;
}

/*============================================================================*/
/**
 *@brief set config always report
 *@test AT+ALWAYS=enable
 */
static qATCLI_Response_t AT_Callback_AlwaysReport( qATCLI_Handler_t parser, qATCLI_PreCmd_t param){
	qATCLI_Response_t RetValue = QATCLI_ERROR;

	switch( param->Type ){
	case QATCLI_CMDTYPE_ACT: // AT+cmd
		//RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_READ:

		RetValue = QATCLI_NORESPONSE;
		break;
	case QATCLI_CMDTYPE_PARA:
			AppData_Config.alwaysSendReportIsActive = param->GetArgInt(1) ;
		RetValue = QATCLI_OK;
		break;

	case QATCLI_CMDTYPE_TEST:
		sprintf(parser->Output,"%s%s",AT_CMD_STR_ALWAYS,"=enable[0-1]");
		RetValue = QATCLI_OK;
		break;
	default : break;
	}
	return RetValue;
}

/*============================================================================*/
/**
 *@brief set config downlink
 *@test AT+DL=enable
 */
static qATCLI_Response_t AT_Callback_Downlink( qATCLI_Handler_t parser, qATCLI_PreCmd_t param){
	qATCLI_Response_t RetValue = QATCLI_ERROR;

	switch( param->Type ){
	case QATCLI_CMDTYPE_ACT: // AT+cmd
		//RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_READ:

		RetValue = QATCLI_NORESPONSE;
		break;
	case QATCLI_CMDTYPE_PARA:
			AppData_Config.downlinkIsActive = param->GetArgInt(1) ;
		RetValue = QATCLI_OK;
		break;

	case QATCLI_CMDTYPE_TEST:
		sprintf(parser->Output,"%s%s",AT_CMD_STR_DL,"=enable[0-1]");
		RetValue = QATCLI_OK;
		break;
	default : break;
	}
	return RetValue;
}


/*============================================================================*/
/**
 *@brief set config event color and pulsation number
 *@test AT+pulsed=npul,cev1,cev2,cev3,cevc
 */
static qATCLI_Response_t AT_Callback_Pulsation( qATCLI_Handler_t parser, qATCLI_PreCmd_t param){
	qATCLI_Response_t RetValue = QATCLI_ERROR;

	switch( param->Type ){
	case QATCLI_CMDTYPE_ACT: // AT+cmd
		//RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_READ:

		RetValue = QATCLI_NORESPONSE;
		break;
	case QATCLI_CMDTYPE_PARA:
			AppData_Config.NumPulsation = param->GetArgInt(1) ;
			AppData_Config.Pulsation_1.rgb = param->GetArgInt(2) ;
			AppData_Config.Pulsation_2.rgb = param->GetArgInt(3) ;
			AppData_Config.Pulsation_3.rgb = param->GetArgInt(4) ;
			AppData_Config.Pulsation_Cancel.rgb = param->GetArgInt(5) ;
		RetValue = QATCLI_OK;
		break;

	case QATCLI_CMDTYPE_TEST:
		sprintf(parser->Output,"%s%s",AT_CMD_STR_PULSED,"=num event[0-3],Color Ev1,Color Ev2,Color Ev3,Color Cancel\n"
		"Color:\nCOLOR_RGB_BLACK = 0\n"
		"COLOR_RGB_BLUE =1\n"
		"COLOR_RGB_GREEN =2\n"
		"COLOR_RGB_AQUA =3\n"
		"COLOR_RGB_RED= 4\n"
		"COLOR_RGB_FUCHSIA =5\n"
		"COLOR_RGB_YELLOW =6\n"
		"COLOR_RGB_WHITE =7\n"
		);
		RetValue = QATCLI_OK;
		break;
	default : break;
	}
	return RetValue;
}


/*============================================================================*/
/**
 *@brief set config sigfox zone
 *@test AT+RCZ =zone
 *@note zone[0-5] 	enum{ 	WSSFM1XRX_RCZ1 = 0,
						WSSFM1XRX_RCZ2,
						WSSFM1XRX_RCZ3,
						WSSFM1XRX_RCZ4,
						WSSFM1XRX_RCZ5,
						WSSFM1XRX_RCZ6,}
 */
static qATCLI_Response_t AT_Callback_Rcz( qATCLI_Handler_t parser, qATCLI_PreCmd_t param){
	qATCLI_Response_t RetValue = QATCLI_ERROR;

	switch( param->Type ){
	case QATCLI_CMDTYPE_ACT: // AT+cmd
		//RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_READ:

		RetValue = QATCLI_NORESPONSE;
		break;
	case QATCLI_CMDTYPE_PARA:
			AppData_Config.RCZ = param->GetArgInt(1) ;
		RetValue = QATCLI_OK;
		break;

	case QATCLI_CMDTYPE_TEST:
		sprintf(parser->Output,"%s%s",AT_CMD_STR_RCZ,"=zone[0-6]");
		RetValue = QATCLI_OK;
		break;
	default : break;
	}
	return RetValue;
}


/**
 * @brief set config accelerometer
 * @test at+axl=mode,enable,high,med,low   or at+axl=enable,mode,xthresholdhigh,xthresholdlow,ythresholdhigh,ythresholdlow
 * @note mode[1-2] 1-> vibration , 2-> inclination
 * @note xthreshold[0-360]  , ythreshold [0-360]
 * */

static qATCLI_Response_t AT_Callback_Accelerometer( qATCLI_Handler_t parser, qATCLI_PreCmd_t param){
	qATCLI_Response_t RetValue = QATCLI_ERROR;

	switch( param->Type ){
	case QATCLI_CMDTYPE_ACT: // AT+cmd
		//RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_READ:

		RetValue = QATCLI_NORESPONSE;
		break;
	case QATCLI_CMDTYPE_PARA:
		AppData_Config.accelerometer.IsActive = param->GetArgInt(2) ;
		if( (AppData_Config.accelerometer.vibration.IsActive = (param->GetArgInt(1) == 1)) ){  /*vibración*/
			AppData_Config.accelerometer.vibration.low = param->GetArgFlt(5);
			AppData_Config.accelerometer.vibration.med = param->GetArgFlt(4);
			AppData_Config.accelerometer.vibration.high = param->GetArgFlt(3);
		}
		else if( (AppData_Config.accelerometer.inclination.IsActive = (param->GetArgInt(1) == 2) ) ){ /*inclinación*/
			AppData_Config.accelerometer.inclination.x.ThresholdHigh = param->GetArgFlt(3);
			AppData_Config.accelerometer.inclination.x.ThresholdLow = param->GetArgFlt(4);
			AppData_Config.accelerometer.inclination.y.ThresholdHigh = param->GetArgFlt(5);
			AppData_Config.accelerometer.inclination.y.ThresholdLow = param->GetArgFlt(6);
			}else {
					}
		RetValue = QATCLI_OK;
		break;

	case QATCLI_CMDTYPE_TEST:
		sprintf(parser->Output,"%s%s%s%s%s",AT_CMD_STR_AXL,"=mode,enable,high,med,low\n",AT_CMD_STR_AXL,"=enable,mode,xthresholdhigh,xthresholdlow,ythresholdhigh,ythresholdlow","mode[1-2] 1-> vibration , 2-> inclination \n xthreshold[0-360]  , ythreshold [0-360]");
		RetValue = QATCLI_OK;
		break;
	default : break;
	}
	return RetValue;
}



/**
 *@brief Get the API information
 *@test at+info?
 * */
/*============================================================================*/
static qATCLI_Response_t AT_Callback_ApiInfo( qATCLI_Handler_t parser, qATCLI_PreCmd_t param){
	qATCLI_Response_t RetValue = QATCLI_ERROR;

	switch( param->Type ){
	case QATCLI_CMDTYPE_ACT: /*< AT+cmd */
		//RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_READ: /*< AT+cmd? */

		ProjectInformation(1);
		RetValue = QATCLI_NORESPONSE;
		break;
	case QATCLI_CMDTYPE_TEST:
		sprintf(parser->Output,"%s",AT_CMD_STR_INFO);
		RetValue = QATCLI_OK;
		break;
	default : break;
	}
	return RetValue;
}


/**
 *@brief set config repeat payload
 *@test AT+REPEAT=enable
 */
static qATCLI_Response_t AT_Callback_RepeatPayload( qATCLI_Handler_t parser, qATCLI_PreCmd_t param){
	qATCLI_Response_t RetValue = QATCLI_ERROR;

	switch( param->Type ){
	case QATCLI_CMDTYPE_ACT: // AT+cmd
		//RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_READ:

		RetValue = QATCLI_NORESPONSE;
		break;
	case QATCLI_CMDTYPE_PARA:
			AppData_Config.redundanciaIsActive = param->GetArgInt(1) ;
		RetValue = QATCLI_OK;
		break;

	case QATCLI_CMDTYPE_TEST:
		sprintf(parser->Output,"%s%s",AT_CMD_STR_REPEAT,"=enable[0-1]");
		RetValue = QATCLI_OK;
		break;
	default : break;
	}
	return RetValue;

}

/**
 *@brief Get all parameters config
 *@test at+read?
 *@test at+read=1 -> init download
 *@note 		<b>FORMAT: </b>"ADC=%d,%u,%u,%d,%u,%u,TEMP=%d,%u,%u,HUM=%d,%u,%u,AQ=%d,%u,%u,FLAGS=%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,TIME=%d,%d,%d,AXL=%d,%d,%u,%u,%u,%u,%d,%u,%u,%u,COLOR=%d,%d,%d,%d,DI=%d,%d,ID=%s,PAC=%s\r\n"
 *@note
 *@note			<b>ADC=</b>
 *				AppData_Config.adc1.IsActive,AppData_Config.adc1.ThresholdHigh*1000,AppData_Config.adc1.ThresholdLow,


@note			AppData_Config.adc2.IsActive,AppData_Config.adc2.ThresholdHigh*1000,AppData_Config.adc2.ThresholdLow,

*@note			<b>TEMPERATURE=</b>
*				AppData_Config.temperature.IsActive,AppData_Config.temperature.ThresholdHigh*1000,AppData_Config.temperature.ThresholdLow,

*@note			<b>HUMIDITY=</b>AppData_Config.humidity.IsActive,
				AppData_Config.humidity.ThresholdHigh,
				AppData_Config.humidity.ThresholdLow,

*@note			<b>AQ</b>=AppData_Config.airquality.IsActive,
				AppData_Config.airquality.ThresholdHigh,
				AppData_Config.airquality.ThresholdLow,

@note			<b>FLAGS=</b>
				AppData_Config.LowBattSoc,
				AppData_Config.LowBattmV,
				AppData_Config.GPS_LocIsActive,
				AppData_Config.WIFI_LocIsActive,
				AppData_Config.alwaysSendReportIsActive,
				AppData_Config.redundanciaIsActive,
				AppData_Config.downlinkIsActive,
				AppData_Config.keepAlive,
				AppData_Config.NumPulsation,
				AppData_Config.onlySendLocation,
				AppData_Config.idDevice,
				AppData_Config.DoCtrl,
				AppData_Config.RCZ,

*@note			<b>TIME=</b>AppData_Config.time.hour,
				AppData_Config.time.min,
				AppData_Config.time.sec,

*@note			<b>AXL=</b>
*@note
				AppData_Config.accelerometer.inclination.IsActive,
				AppData_Config.accelerometer.inclination.x.ThresholdHigh,
				AppData_Config.accelerometer.inclination.x.ThresholdLow,
				AppData_Config.accelerometer.inclination.y.ThresholdHigh,
				AppData_Config.accelerometer.inclination.y.ThresholdLow,
				AppData_Config.accelerometer.vibration.IsActive,
				AppData_Config.accelerometer.vibration.high,
				AppData_Config.accelerometer.vibration.med,
				AppData_Config.accelerometer.vibration.low,

*@note			<b>COLOR=</b>AppData_Config.Pulsation_1.rgb,
				AppData_Config.Pulsation_2.rgb,
				AppData_Config.Pulsation_3.rgb,
				AppData_Config.Pulsation_Cancel.rgb,

*@note			<b>DI=</b>AppData_Config.DI_1,
				AppData_Config.DI_2,

*@note			<b>IP=</b>AppData_Config.Id_module,
				<b>PAC=</b>AppData_Config.Pac_module
 *
 * */



static qATCLI_Response_t AT_Callback_Read( qATCLI_Handler_t parser, qATCLI_PreCmd_t param){
	qATCLI_Response_t RetValue = QATCLI_ERROR;

	switch( param->Type ){
	case QATCLI_CMDTYPE_ACT: /*< AT+cmd */
		//RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_PARA:
			if( param->GetArgInt(1) == 1){
				qTask_EventFlags_Modify(&TaskApplicationFSM, QEVENTFLAG_01, 1);
			}
		RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_READ: /*< AT+cmd? */
		sprintf(parser->Output,"ADC=%d,%u,%u,%d,%u,%u,TEMP=%d,%u,%u,HUM=%d,%u,%u,AQ=%d,%u,%u,FLAGS=%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,TIME=%d,%d,%d,AXL=%d,%u,%u,%u,%u,%d,%u,%u,%u,COLOR=%d,%d,%d,%d,DI=%d,%d,ID=%s,PAC=%s\r\n",
				AppData_Config.adc1.IsActive,
				(uint16_t)AppData_Config.adc1.ThresholdHigh,
				(uint16_t)AppData_Config.adc1.ThresholdLow,

				AppData_Config.adc2.IsActive,
				(uint16_t)AppData_Config.adc2.ThresholdHigh,
				(uint16_t)AppData_Config.adc2.ThresholdLow,

				AppData_Config.temperature.IsActive,
				(uint16_t)AppData_Config.temperature.ThresholdHigh,
				(uint16_t)AppData_Config.temperature.ThresholdLow,

				AppData_Config.humidity.IsActive,
				(uint16_t)AppData_Config.humidity.ThresholdHigh,
				(uint16_t)AppData_Config.humidity.ThresholdLow,

				AppData_Config.airquality.IsActive,
				(uint16_t)AppData_Config.airquality.ThresholdHigh,
				(uint16_t)AppData_Config.airquality.ThresholdLow,

				/*flags*/
				AppData_Config.LowBattSoc,
				AppData_Config.LowBattmV,
				AppData_Config.GPS_LocIsActive,
				AppData_Config.WIFI_LocIsActive,
				AppData_Config.alwaysSendReportIsActive,
				AppData_Config.redundanciaIsActive,
				AppData_Config.downlinkIsActive,
				AppData_Config.keepAlive,
				AppData_Config.NumPulsation,
				AppData_Config.onlySendLocation,
				AppData_Config.idDevice,
				AppData_Config.DoCtrl,
				AppData_Config.RCZ,

				AppData_Config.time.hour,
				AppData_Config.time.min,
				AppData_Config.time.sec,


				AppData_Config.accelerometer.inclination.IsActive,  // mode inclinación
				(uint16_t)AppData_Config.accelerometer.inclination.x.ThresholdHigh,
				(uint16_t)AppData_Config.accelerometer.inclination.x.ThresholdLow,
				(uint16_t)AppData_Config.accelerometer.inclination.y.ThresholdHigh,
				(uint16_t)AppData_Config.accelerometer.inclination.y.ThresholdLow,
				AppData_Config.accelerometer.vibration.IsActive,   //mode vibración
				(uint16_t)AppData_Config.accelerometer.vibration.high,
				(uint16_t)AppData_Config.accelerometer.vibration.med,
				(uint16_t)AppData_Config.accelerometer.vibration.low,

				AppData_Config.Pulsation_1.rgb,
				AppData_Config.Pulsation_2.rgb,
				AppData_Config.Pulsation_3.rgb,
				AppData_Config.Pulsation_Cancel.rgb,

				AppData_Config.DI_1,
				AppData_Config.DI_2,

				AppData_Config.Id_module,
				AppData_Config.Pac_module

		);

		qDebug_Decimal(AppData_Config.DI_1 );
		qDebug_Decimal(	AppData_Config.DI_2);
		qDebug_Decimal(	AppData_Config.GPS_LocIsActive );
		qDebug_Decimal( 	AppData_Config.LowBattSoc );
		qDebug_Decimal(AppData_Config.NumPulsation );;
		qDebug_Decimal(  	AppData_Config.Pulsation_1.rgb );
		qDebug_Decimal(  	AppData_Config.Pulsation_2.rgb );
		qDebug_Decimal(	AppData_Config.Pulsation_3.rgb );
		qDebug_Decimal(  	AppData_Config.Pulsation_Cancel.rgb );
		qDebug_Decimal( 	AppData_Config.RCZ );
		qDebug_Decimal( 	AppData_Config.WIFI_LocIsActive);
		qDebug_Decimal( 	AppData_Config.accelerometer.IsActive);
		qDebug_Float( 	AppData_Config.accelerometer.inclination.x.ThresholdLow );
		qDebug_Float( 	AppData_Config.accelerometer.inclination.x.ThresholdHigh);
		qDebug_Float(  	AppData_Config.accelerometer.inclination.y.ThresholdLow );
		qDebug_Float(  	AppData_Config.accelerometer.inclination.y.ThresholdHigh );

		qDebug_Float( 	AppData_Config.accelerometer.vibration.IsActive );
		qDebug_Float( 	AppData_Config.accelerometer.vibration.high);
		qDebug_Float(  	AppData_Config.accelerometer.vibration.med);
		qDebug_Float(  	AppData_Config.accelerometer.vibration.low );

		qDebug_Decimal( 	AppData_Config.adc1.IsActive );
		qDebug_Float( 	AppData_Config.adc1.ThresholdLow );
		qDebug_Float(  	AppData_Config.adc1.ThresholdHigh );
		qDebug_Decimal( 	AppData_Config.adc2.IsActive );
		qDebug_Float(  	AppData_Config.adc2.ThresholdLow );
		qDebug_Float(  	AppData_Config.adc2.ThresholdHigh );
		qDebug_Decimal(  	AppData_Config.airquality.IsActive );
		qDebug_Float( 	AppData_Config.airquality.ThresholdLow );
		qDebug_Float( 	AppData_Config.airquality.ThresholdHigh );
		qDebug_Decimal( 	AppData_Config.alwaysSendReportIsActive );
		qDebug_Decimal(  	AppData_Config.downlinkIsActive );
		qDebug_Decimal( 	AppData_Config.humidity.IsActive );
		qDebug_Float( 	AppData_Config.humidity.ThresholdLow );
		qDebug_Float(	AppData_Config.humidity.ThresholdHigh );

		qDebug_Decimal( 	AppData_Config.temperature.IsActive );
		qDebug_Float(	AppData_Config.temperature.ThresholdLow );
		qDebug_Float(  	AppData_Config.temperature.ThresholdHigh );
		qDebug_Decimal( 	AppData_Config.keepAlive );
		qDebug_Decimal( 	AppData_Config.redundanciaIsActive);
		qDebug_Decimal( 	AppData_Config.time.hour );
		qDebug_Decimal( 	AppData_Config.time.min );
		qDebug_Decimal( 	AppData_Config.time.sec );
		qDebug_Decimal( 	AppData_Config.onlySendLocation );
		qDebug_Decimal( 	AppData_Config.idDevice );
		qDebug_Decimal(		AppData_Config.DoCtrl);
		qDebug_String(AppData_Config.Id_module);
		qDebug_String(AppData_Config.Pac_module);
		qDebug_Decimal(AppData_Config.LowBattmV);
		RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_TEST:
		sprintf(parser->Output,"%s",AT_CMD_STR_READ);
		RetValue = QATCLI_OK;
		break;
	default : break;
	}
	return RetValue;
}

/**
 *@brief set config only location, skip sensor frame
 *@test AT+onlyloc=enable
 */
static qATCLI_Response_t AT_Callback_OnlySendLocation( qATCLI_Handler_t parser, qATCLI_PreCmd_t param){
	qATCLI_Response_t RetValue = QATCLI_ERROR;

	switch( param->Type ){
	case QATCLI_CMDTYPE_ACT: // AT+cmd
		//RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_READ:

		RetValue = QATCLI_NORESPONSE;
		break;
	case QATCLI_CMDTYPE_PARA:
			AppData_Config.onlySendLocation = param->GetArgInt(1) ;
		RetValue = QATCLI_OK;
		break;

	case QATCLI_CMDTYPE_TEST:
		sprintf(parser->Output,"%s%s",AT_CMD_STR_ONLYLOC,"=enable[0-1]");
		RetValue = QATCLI_OK;
		break;
	default : break;
	}
	return RetValue;
}

/**
 *@brief set config id device
 *@test AT+iddev=dev
 *@test at+iddev?
 *@note dev[0-6]  enum {
					APP_ID_DEVICE_WSQ = 0,
					APP_ID_DEVICE_GSQ ,
					APP_ID_DEVICE_ISMC,
					APP_ID_DEVICE_ISMC_POLLUTION,
					APP_ID_DEVICE_ISMC_MOBILITY,
					APP_ID_DEVICE_ISMC_WATER,
					APP_ID_DEVICE_UNKNOWN
				}App_idDevice_t;
 default 0.
 */
static qATCLI_Response_t AT_Callback_IdDevice( qATCLI_Handler_t parser, qATCLI_PreCmd_t param){
	qATCLI_Response_t RetValue = QATCLI_ERROR;

	switch( param->Type ){
	case QATCLI_CMDTYPE_ACT: // AT+cmd
		//RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_READ:
		sprintf( parser->Output, "%u", AppData_Config.idDevice);
		RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_PARA:
		AppData_Config.idDevice = param->GetArgInt(1) ;

		RetValue = QATCLI_OK;
		break;

	case QATCLI_CMDTYPE_TEST:
		sprintf(parser->Output,"%s%s",AT_CMD_STR_IDEV,"=device\n"
		"dev[0-6]:\nAPP_ID_DEVICE_WSQ = 0\n"
					"APP_ID_DEVICE_GSQ =1\n"
					"APP_ID_DEVICE_ISMC =2\n"
					"APP_ID_DEVICE_ISMC_POLLUTION=3\n"
					"APP_ID_DEVICE_ISMC_MOBILITY=4\n"
					"APP_ID_DEVICE_ISMC_WATER=5\n"
					"APP_ID_DEVICE_UNKNOWN=6\n"
				);
		RetValue = QATCLI_OK;
		break;
	default : break;
	}
	return RetValue;
}

/**
 *@brief set digital output
 *@test AT+gpo=enable
 */
STATIC qATCLI_Response_t AT_Callback_DoCtrl( qATCLI_Handler_t parser, qATCLI_PreCmd_t param){


	qATCLI_Response_t RetValue = QATCLI_ERROR;

	switch( param->Type ){
	case QATCLI_CMDTYPE_ACT: // AT+cmd
		//RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_READ:
		sprintf( parser->Output, "%d", AppData_Config.DoCtrl);
		RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_PARA:
		AppData_Config.DoCtrl = param->GetArgInt(1) ;
		BSP_GPIO_WRITE_OUT_CTL(AppData_Config.DoCtrl);
		RetValue = QATCLI_OK;
		break;

	case QATCLI_CMDTYPE_TEST:
		sprintf(parser->Output,"%s%s",AT_CMD_STR_GPO,"=enable[0-1]");
		RetValue = QATCLI_OK;
		break;
	default : break;
	}
	return RetValue;
}



/**
 *@brief Reset factory
 *@test at+resetf
 * */
static qATCLI_Response_t AT_Callback_ResetFactory( qATCLI_Handler_t parser, qATCLI_PreCmd_t param){
	qATCLI_Response_t RetValue = QATCLI_ERROR;

	switch( param->Type ){
	case QATCLI_CMDTYPE_ACT: /*< AT+cmd */
		BSP_FLASH_RESTORE(BSP_FLASH_INIT_ADDR_RESERVED_DATA_CONF,sizeof(AppData_Config));

		CounterKeepAlive = 0;
		BSP_FLASH_WRITE(BSP_FLASH_INIT_ADDR_RESERVED_DATA_CONF + sizeof(AppData_Config) + 4 ,&CounterKeepAlive,1 ); /*APP_POS_FLASH_COUNT_KEEP_ALIVE*/

		RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_TEST:
		sprintf(parser->Output,"%s",AT_CMD_STR_RESETF);
		RetValue = QATCLI_OK;
		break;
	default : break;
	}
	return RetValue;
}

/*============================================================================*/

/**
 *@brief save configuration in to flash
 *@test at+save
 * */
static qATCLI_Response_t AT_Callback_Save( qATCLI_Handler_t parser, qATCLI_PreCmd_t param){
	qATCLI_Response_t RetValue = QATCLI_ERROR;

	switch( param->Type ){
	case QATCLI_CMDTYPE_ACT: /*< AT+cmd */
		qTask_EventFlags_Modify(&TaskApplicationFSM, QEVENTFLAG_01, 0);
		BSP_FLASH_WRITE(BSP_FLASH_INIT_ADDR_RESERVED_DATA_CONF, &AppData_Config,sizeof(AppData_Config));
		//BSP_FLASH_WRITE(BSP_FLASH_INIT_ADDR_RESERVED_DATA_CONF + sizeof(AppData_Config) + 4 ,&idDevice,1 );

		RetValue = QATCLI_OK;
		break;
	case QATCLI_CMDTYPE_TEST:
		sprintf(parser->Output,"%s",AT_CMD_STR_SAVE);
		RetValue = QATCLI_OK;
		break;
	default : break;
	}
	return RetValue;
}


void AT_CLI_CustomCallback(uint8_t * Buf , uint32_t Len){
	(void)qATCLI_ISRHandlerBlock(&ATCommandParser, (char*)Buf, Len ); /*feed the AT CLI input*/
}

void ProjectInformation(int putsUsb) {
	BSP_UART_DEBUG_PUTS("=========================================\r\n");
	BSP_UART_DEBUG_PUTS("iButton  ");
	BSP_UART_DEBUG_PUTS(StrIdDevice[AppData_Config.idDevice] );
	BSP_UART_DEBUG_PUTS(APP_CONFIG_BUILD_VER "\r\n");
	BSP_UART_DEBUG_PUTS(INF_STRING );
	BSP_UART_DEBUG_PUTS("Time Report (h:m:s) : " );
	BSP_UART_DEBUG_PUTS(qIOUtil_ItoA(AppData_Config.time.hour , StrReportTime,10));
	BSP_UART_DEBUG_PUTS(":");
	BSP_UART_DEBUG_PUTS(qIOUtil_ItoA(AppData_Config.time.min , StrReportTime,10));
	BSP_UART_DEBUG_PUTS(":");
	BSP_UART_DEBUG_PUTS(qIOUtil_ItoA(AppData_Config.time.sec , StrReportTime,10));
	BSP_UART_DEBUG_PUTS("\r\nKeep alive: ");
	BSP_UART_DEBUG_PUTS(qIOUtil_ItoA(AppData_Config.keepAlive , StrReportTime,10));
	BSP_UART_DEBUG_PUTS("\r\nDownlink: ");
	BSP_UART_DEBUG_PUTS(qIOUtil_ItoA(AppData_Config.downlinkIsActive, StrReportTime,10));
	BSP_UART_DEBUG_PUTS("\r\n" AUT_STRING "\r\n");
	BSP_UART_DEBUG_PUTS(__DATE__ "-" __TIME__ "\r\n");
	BSP_UART_DEBUG_PUTS("=========================================\r\n");

	char bufferputs[500];

	if(1 == putsUsb){
		sprintf(bufferputs,"%s%s%s%s\r\n%s%s%02d:%02d:%02d%s%s%s%s%s%s%s",
				"=========================================\r\n",
				"iButton  ",
				StrIdDevice[AppData_Config.idDevice] ,
				APP_CONFIG_BUILD_VER,
				INF_STRING,
				"Time Report (h:m:s) : ",
				AppData_Config.time.hour,
				AppData_Config.time.min ,
				AppData_Config.time.sec ,
				"\r\nKeep alive: ",
				qIOUtil_ItoA(AppData_Config.keepAlive , StrReportTime,10),
				"\r\nDownlink: ",
				qIOUtil_ItoA(AppData_Config.downlinkIsActive, StrReportTime,10),
				("\r\n" AUT_STRING "\r\n"),
				(__DATE__ "-" __TIME__ "\r\n"),
				("=========================================\r\n")
				);
		BSP_USB_PUTS((uint8_t*)bufferputs);

	}
}
