/*WaterLevel.c*/

#include "iodefine.h"
#include "WaterLevel.h"

int WaterLevel_get_water_level(){
	
	int water_level = 0;
	
	P8.DDR = 0x00; //ì¸óÕÇ…ê›íË
	
	if(P8.DR.BIT.B4 == 1){
	    water_level = 5;
		
	}else if(P8.DR.BIT.B3 == 1){
	    water_level = 4;
		
	}else if(P8.DR.BIT.B2 == 1){
	    water_level = 3;
		
	}else if(P8.DR.BIT.B1 == 1){
	    water_level = 2;
		
	}else if(P8.DR.BIT.B0 == 1){
	    water_level = 1;
		
	}
	
	return water_level;
}
