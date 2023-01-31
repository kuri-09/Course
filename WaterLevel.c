/*WaterLevel.c*/

#include "iodefine.h"

unsigned char WaterLevel_get_water_level(){
	
	unsigned char water_level = 0;
	
	water_level = (P8.DR.BYTE & 0x1f);
	
	return water_level;
}