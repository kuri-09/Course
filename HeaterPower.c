//HeaterPower.c
#include "iodefine.h"

void HeaterPower_turn_on(){
	P6.DR.BIT.B6 = 1;
	
}

void HeaterPower_turn_off(){
	P6.DR.BIT.B6 = 0;
}

