//WaterLevelMeter.c

#include "iodefine.h"

void WaterLevelMeter_show_water_level(unsigned char display_water_level/*, unsigned char pb_state*/){

	if(display_water_level == 0x1f)
	    display_water_level = 0x0f;

	PB.DR.BYTE = ((PB.DR.BYTE & 0xf0) | display_water_level);
	
	//PB.DDR = 0xff;
}