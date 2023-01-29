//ExternalInterrupt.c

#include "KettleSystem.h"
#include "struct.h"

#include "iodefine.h"

/*extern�錾*//*�\���̂̐錾*/
extern SYSTEM_CLASS SYSTEM;
extern INTERRUPT_CLASS INTERRUPT;
extern MANAGER_CLASS MANAGER;

void isr_irq4(){
	
	//static flag flag_type;
	static int cnt;
	cnt++;
	
	INTERRUPT.INPUT.COVER_STATE = COVER_OPEN;
	
	//���荞�݃t���O�̃N���A
	if(INTC.ISR.BIT.IRQ4F != 0){//��Ԃ̃��[�h

		INTC.ISR.BIT.IRQ4F = 0;

	}
}
