//ExternalInterrupt.c

#include "KettleSystem.h"
#include "struct.h"

#include "iodefine.h"

/*extern宣言*//*構造体の宣言*/
extern SYSTEM_CLASS SYSTEM;
extern INTERRUPT_CLASS INTERRUPT;
extern MANAGER_CLASS MANAGER;

void isr_irq4(){
	
	//static flag flag_type;
	static int cnt;
	cnt++;
	
	INTERRUPT.INPUT.COVER_STATE = COVER_OPEN;
	
	//割り込みフラグのクリア
	if(INTC.ISR.BIT.IRQ4F != 0){//状態のリード

		INTC.ISR.BIT.IRQ4F = 0;

	}
}
