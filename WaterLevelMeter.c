//WaterLevelMeter.c

#include "iodefine.h"
#include "WaterLevelMeter.h"

void WaterLevelMeter_show_water_level(unsigned char water_level/*, unsigned char pb_state*/){

	PB.DR.BYTE = water_level;
	
	PB.DDR = 0xff;
}