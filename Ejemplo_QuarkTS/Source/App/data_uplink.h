/*
 * data_uplink.h
 *
 *  Created on: Sep 15, 2020
 *      Author: Julian
 */

#ifndef SOURCE_APP_DATA_UPLINK_H_
#define SOURCE_APP_DATA_UPLINK_H_

#include <stdint.h>
#include <bsp_remapping.h>

/*types*/
typedef enum {
	APPDATAUP_SENSORS = 0b011,	 /*x11 forzar no es mac*/
	APPDATAUP_GPS = 0b111,
	APPDATAUP_EVENT_1 =0b000,
	APPDATAUP_EVENT_2 =0b001,
	APPDATAUP_EVENT_3 =0b010
}AppDataUp_types_t;


/**
 * @brief Structure to hold the application variables.
 */
#pragma pack( push,1)
/*tipo*/
typedef struct{
	unsigned type 		: 3;
	unsigned LowBattery   : 1;
	unsigned Periodic	: 1;
	unsigned KeepAlive 	: 1;
	unsigned DI1  		: 1;
	unsigned DI2  		: 1;
}AppDataUp_Id_bf;


/*sensors*/
typedef struct{
	union {
		unsigned dummy :8;
		unsigned eventClick	: 8;
		unsigned AirQuality	: 16;
	};

	unsigned adc1		: 12;
	unsigned adc2		: 12;
	unsigned pitch		: 12;
	unsigned roll		: 12;
	unsigned hum		: 8;
	unsigned temp		: 8;
	unsigned soc 		: 8;
}AppDataUp_Sensor_bf;
#pragma pack( pop)


#pragma pack( push,1)
typedef union{
	uint8_t AllBytes[12];

	struct{
		AppDataUp_Sensor_bf sen_bf;
		AppDataUp_Id_bf  id;
	}Sensors;

	struct{

		uint8_t others[3]; /*restantes 3bytes*/
		float Longitude;
        float Latitude;
        AppDataUp_Id_bf	id;
	}GPSLocation;

	struct{
		uint8_t MAC2[6];
        uint8_t MAC1[6];
	 }WiFiLocation;

}AppDataUp_Frame_t;
#pragma pack( pop)



/*type(1) acc(3) adc(3) H+T(2)   vacio-click(2) SOC(1)
	  ↓
	 * battlow
	 * periodico
	 * keep-alive
	 * DI1
	 * DI2
	 * type(3 bits)
 *
 * */

/*type MAC1     | 00 00 00 00 00 */
/* MAC1     |      MAC2     */
/*type Lat | Long |  status ttff3d soc */

extern AppDataUp_Frame_t Isquare_Data ;


#endif /* SOURCE_APP_DATA_UPLINK_H_ */
