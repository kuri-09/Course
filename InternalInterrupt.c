//InternalInterrupt.c

#include "KettleSystem.h"
#include "Manager.h"
//#include "Display.h"

#include "iodefine.h"

#include <machine.h>


//16ビット幅
void isr_imia1(){
	
	static int cnt;
	unsigned char btn_state;
	int water_lv;
	int cover_state;
	
	static flag flag_type;
	static btn btn_type;
	
	cnt++;
	
	//10ms毎に処理を行う
	if(cnt%10 == 0){
		
		flag_type = show_timer;
		Manager_interrupt(flag_type, 0, 0, 0);
		
		if((cnt%100) == 0){
			
			//ボタンの状態読み込み
			flag_type = button;
			btn_state = Button_get_botan_state();
			Manager_interrupt(flag_type, btn_state, 0, 0);
			
			//ふたの状態読み込み
			flag_type = cover;
			cover_state = Cover_get_cover_state();
			Manager_interrupt(flag_type, 0, 0, cover_state);
			
			if(cnt == 1000){
				
				//水位の状態読み込み
				flag_type = water_level;
				water_lv = WaterLevel_get_water_level();
				Manager_interrupt(flag_type, 0, water_lv, 0);
				
				cnt = 0;
			}
		}
	}
	
	//割り込みフラグのクリア
	if(ITU1.TSR.BIT.IMFA != 0){//状態のリード

		ITU1.TSR.BIT.IMFA = 0;

	}
}

/*
//16ビット幅
void isr_imia2(){
	
	
	
	/*割り込みフラグのクリア*/
	/*if(ITU2.TSR.BIT.IMFA != 0){//状態のリード

		ITU2.TSR.BIT.IMFA = 0;

	}
}
*/