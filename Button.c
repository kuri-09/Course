//Button.c

#include "iodefine.h"
#include "Button.h"

#include <machine.h>

int Button_get_botan_state(){
	
	unsigned char btn_state = 0x00;
	
	P4.DDR = 0x00; //“ü—Í‚Éİ’è
	
	if(P4.DR.BIT.B0 == 1)
	    btn_state += 0x01;
	if(P4.DR.BIT.B1 == 1)
	    btn_state += 0x02;
	if(P4.DR.BIT.B2 == 1)
	    btn_state += 0x04;
	if(P4.DR.BIT.B3 == 1)
	    btn_state += 0x08;	
	if(P4.DR.BIT.B4 == 1)
	    btn_state += 0x10;
	
	return btn_state;
}
