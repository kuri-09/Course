////BoilLamp.c

#include "iodefine.h"
#include "BoilLamp.h"

//���������v��_��������
void BoilLamp_turn_on_lamp(){
	
	PB.DR.BIT.B4 = 1;
	//PB.DDR = 0xff;
}

//���������v������������
void BoilLamp_turn_off_lamp(){
	
	PB.DR.BIT.B4 = 0;
	//PB.DDR = 0xff;
}