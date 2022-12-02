//LockLamp.c

#include "iodefine.h"
#include "LockLamp.h"

//ロックランプを点灯させる
void Lock_Lamp_turn_on_lamp(){
	
	PB.DR.BIT.B6 = 1;
	PB.DDR = 0xff;
}

//ロックランプを消灯させる
void Lock_Lamp_turn_off_lamp(){
	
	PB.DR.BIT.B6 = 0;
	PB.DDR = 0xff;
}