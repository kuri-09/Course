//Button.c

#include "iodefine.h"
#include "Button.h"

#include <machine.h>

int Button_get_button_state(){
	
	unsigned char btn_state = 0x00;
	
	//P4.DDR = 0x00; //入力に設定
	
	btn_state = (P4.DR.BYTE & 0x1f);
	
	return btn_state;
}
