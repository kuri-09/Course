//LockLamp.c

#include "iodefine.h"
#include "LockLamp.h"

//���b�N�����v��_��������
void LockLamp_turn_on_lamp(){
	
	PB.DR.BIT.B6 = 1;
	//PB.DDR = 0xff;
}

//���b�N�����v������������
void LockLamp_turn_off_lamp(){
	
	PB.DR.BIT.B6 = 0;
	//PB.DDR = 0xff;
}