//Buzzer.c
#include "iodefine.h"
#include "Buzzer.h"

void Buzzer_turn_on(){
	P6.DR.BIT.B5 = 1;
}

void Buzzer_turn_on_enable(){
	P6.DR.BIT.B4 = 1;
}

void Buzzer_turn_off(){
	P6.DR.BIT.B5 = 0;
}

void Buzzer_turn_off_enable(){
	P6.DR.BIT.B4 = 0;
}