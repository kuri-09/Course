//Cover.c

#include "iodefine.h"

int Cover_get_cover_state(){
	
	int cover_state = 0;
	
	//P9.DDR = 0x00; //入力に設定
	
	//閉まっているとき
	if(P9.DR.BIT.B4 == 1){
	     cover_state = 1;
		 
	}
	return cover_state;
}