/**
 * @file AT_commands.h
 * @brief interface Command line AT
 * @date Mar 3, 2020
 * @author Esp.Ing.Julian Bustamante N
 */

#ifndef INC_SERVICE_TASK_AT_COMMANDS_H_
#define INC_SERVICE_TASK_AT_COMMANDS_H_

#include <stdint.h>

#define AT_CLI_MAX_INPUT_BUFF_SIZE			128 	/*!< length buffer parser output CLI AT*/
#define AT_CLI_MAX_OUTPUT_BUFF_SIZE			512		/*!< length buffer parser input CLI AT*/

#define AT_CMD_STR_PAC      "at+pac"
#define AT_CMD_STR_ID       "at+id"
#define AT_CMD_STR_BATT     "at+batt"
#define AT_CMD_STR_ADC      "at+adc"
#define AT_CMD_STR_DI      "at+di"
#define AT_CMD_STR_TIME     "at+time"
#define AT_CMD_STR_HT       "at+ht"
#define AT_CMD_STR_AIRQ     "at+airq"
#define AT_CMD_STR_GPS      "at+gps"
#define AT_CMD_STR_WIFI     "at+wifi"
#define AT_CMD_STR_ALWAYS   "at+always"
#define AT_CMD_STR_DL       "at+dl"
#define AT_CMD_STR_PULSED   "at+pulsed"
#define AT_CMD_STR_RCZ      "at+rcz"
#define AT_CMD_STR_AXL      "at+axl"
#define AT_CMD_STR_INFO     "at+info"
#define AT_CMD_STR_REPEAT   "at+repeat"
#define AT_CMD_STR_READ     "at+read"
#define AT_CMD_STR_ONLYLOC  "at+onlyloc"
#define AT_CMD_STR_IDEV     "at+iddev"
#define AT_CMD_STR_GPO      "at+gpo"
#define AT_CMD_STR_RESETF      "at+resetf"
#define AT_CMD_STR_SAVE      "at+save"

/**
 * @brief This function configure AT command line
 * */
void AT_Command_Init(void);

/**
 * @brief This function is call for receive data by vcp(usb)
 * @param buf: receive data
 * @param Len: length of data
 * */
void AT_CLI_CustomCallback(uint8_t * Buf , uint32_t Len);

void ProjectInformation(int putsUsb);

/*============================================================================*/


/*commands*/




#endif /* INC_SERVICE_TASK_AT_COMMANDS_H_ */
