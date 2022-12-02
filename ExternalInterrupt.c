//ExternalInterrupt.c

#include "KettleSystem.h"
#include "Manager.h"
#include "Display.h"

#include "iodefine.h"

#include    <machine.h>

void isr_irq4(){
	
	//static flag flag_type;
	static int cnt;
	cnt++;
	
	Boil_Lamp_turn_off_lamp();
	Keep_Lamp_turn_off_lamp();
	Lock_Lamp_turn_off_lamp();
	
	//���荞�݃t���O�̃N���A
	if(INTC.ISR.BIT.IRQ4F != 0){//��Ԃ̃��[�h

		INTC.ISR.BIT.IRQ4F = 0;

	}
}
