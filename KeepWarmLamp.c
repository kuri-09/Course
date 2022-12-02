//KeepWarmLamp.c

#include "iodefine.h"
#include "KeepWarmLamp.h"

void Keep_Lamp_turn_on_lamp(){
	
	PB.DR.BIT.B5 = 1;
	PB.DDR = 0xff;
}

void Keep_Lamp_turn_off_lamp(){
	
	PB.DR.BIT.B5 = 0;
	PB.DDR = 0xff;
}