//ExternalInterrupt.c

#include "KettleSystem.h"
#include "iodefine.h"

/*extern宣言*/
extern int cover_state;

void isr_irq4(){
	
	//static flag flag_type;
	static int cnt;
	cnt++;
	
	cover_state = 0;
	Boil_Lamp_turn_off_lamp();
	Keep_Lamp_turn_off_lamp();
	Lock_Lamp_turn_off_lamp();
	
	//割り込みフラグのクリア
	if(INTC.ISR.BIT.IRQ4F != 0){//状態のリード

		INTC.ISR.BIT.IRQ4F = 0;

	}
}
