//LockLamp.c

#include "iodefine.h"

//ロックランプを点灯させる
void LockLamp_turn_on_lamp(){
	
	PB.DR.BIT.B6 = 1;
	//PB.DDR = 0xff;
}

//ロックランプを消灯させる
void LockLamp_turn_off_lamp(){
	
	PB.DR.BIT.B6 = 0;
	//PB.DDR = 0xff;
}