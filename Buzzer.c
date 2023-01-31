//Buzzer.c
#include "iodefine.h"

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

void Buzzer_ring_buzzer(int times){
	
	int i = 0;

	for(i = 0; i < times; i++){
		
		Buzzer_turn_on_enable();
	    Buzzer_turn_on();
	    wait_ms(100);
	    Buzzer_turn_off();
	    Buzzer_turn_off_enable();
	    wait_ms(50);
		
	}
	
}