////BoilLamp.c

#include "iodefine.h"
#include "BoilLamp.h"

//•¦“«ƒ‰ƒ“ƒv‚ğ“_“”‚³‚¹‚é
void Boil_Lamp_turn_on_lamp(){
	
	PB.DR.BIT.B4 = 1;
	PB.DDR = 0xff;
}

//•¦“«ƒ‰ƒ“ƒv‚ğÁ“”‚³‚¹‚é
void Boil_Lamp_turn_off_lamp(){
	
	PB.DR.BIT.B4 = 0;
	PB.DDR = 0xff;
}