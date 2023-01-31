//KeepWarmLamp.c

#include "iodefine.h"

void KeepWarmLamp_turn_on_lamp(){
	
	PB.DR.BIT.B5 = 1;
	//PB.DDR = 0xff;
}

void KeepWarmLamp_turn_off_lamp(){
	
	PB.DR.BIT.B5 = 0;
	//PB.DDR = 0xff;
}