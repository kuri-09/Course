//Cover.c

#include "iodefine.h"
#include "Cover.h"

#include <machine.h>

int Cover_get_cover_state(){
	
	int cover_state = 0;
	
	//P9.DDR = 0x00; //“ü—Í‚Éİ’è
	
	//•Â‚Ü‚Á‚Ä‚¢‚é‚Æ‚«
	if(P9.DR.BIT.B4 == 1){
	     cover_state = 1;
		 
	}
	return cover_state;
}