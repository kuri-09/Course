////BoilLamp.c

#include "iodefine.h"
#include "BoilLamp.h"

//���������v��_��������
void Boil_Lamp_turn_on_lamp(){
	
	PB.DR.BIT.B4 = 1;
	PB.DDR = 0xff;
}

//���������v������������
void Boil_Lamp_turn_off_lamp(){
	
	PB.DR.BIT.B4 = 0;
	PB.DDR = 0xff;
}