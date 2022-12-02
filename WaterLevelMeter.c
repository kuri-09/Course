//WaterLevelMeter.c

#include "iodefine.h"
#include "WaterLevelMeter.h"

void WaterLevelMeter_show_water_level(int water_level){

	PB.DR.BIT.B0 = 0;
	PB.DR.BIT.B1 = 0;
	PB.DR.BIT.B2 = 0;
	PB.DR.BIT.B3 = 0;
	
	if(water_level >= 1)
		PB.DR.BIT.B0 = 1;
	if(water_level >= 2)
		PB.DR.BIT.B1 = 1;
	if(water_level >= 3)
		PB.DR.BIT.B2 = 1;
	if(water_level >= 4)
		PB.DR.BIT.B3 = 1;
	
	PB.DDR = 0xff;
}