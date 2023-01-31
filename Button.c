//Button.c

#include "iodefine.h"

int Button_get_button_state(){
	
	unsigned char btn_state = 0x00;
	
	//P4.DDR = 0x00; //“ü—Í‚Éİ’è
	
	btn_state = (P4.DR.BYTE & 0x1f);
	
	return btn_state;
}
