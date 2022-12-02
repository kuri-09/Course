/*Manager.c*/

#include "KettleSystem.h"

#define MINUTE 6000
#define SECOND 100

void Manager_interrupt(int flag_type, unsigned char btn_state, int water_lv, int cover_state){
	
	static int r_time;
	static int water;
	static int cnt_interrupt;
	static int cover_s;
	btn btn_type;
	
	
	
	//タイマ割り込み：時間表示
	if(flag_type == show_timer){
		
		RTimeDisp_show_remaining_time(r_time);
	
	
	//タイマ割り込み：ボタン
	}else if(flag_type == button){
		
		//btn_type = unlock;
		if((btn_state & 0x01) == 0x01){
			Lock_Lamp_turn_on_lamp();
		}else{
			Lock_Lamp_turn_off_lamp();
		}
		
		//btn_type = boil;
		if((btn_state & 0x02) == 0x02){	
			Boil_Lamp_turn_on_lamp();
		}else{
			Boil_Lamp_turn_off_lamp();
		}
		
		//btn_type = supply_water;
		if((btn_state & 0x04) == 0x04){
			if(water != 0)
			    water = water - 1;
			WaterLevelMeter_show_water_level(water);
		}
		
		//btn_type = timer;
		if((btn_state & 0x08) == 0x08){
			if(r_time != 60)
			    r_time += 1;
		    RTimeDisp_show_remaining_time(r_time);
		}
		
		//btn_type = set_keep_mode;
		if((btn_state & 0x10) == 0x10){
			Keep_Lamp_turn_on_lamp();
		}else{
			Keep_Lamp_turn_off_lamp();
		}
	
	
	//タイマ割り込み：水位
	}else if(flag_type == water_level){
		
		//開いているとき
		if(cover_s == 0){
			water = water_lv;
			WaterLevelMeter_show_water_level(water);
		}
	
	
	//タイマ割り込み：ふた
	}else if(flag_type == cover){
		
		cover_s = cover_state;
		
		//閉まっているとき
		if(cover_s == 1){
			Boil_Lamp_turn_on_lamp();
			Keep_Lamp_turn_on_lamp();
			Lock_Lamp_turn_on_lamp();
		}
		
	}
	
	cnt_interrupt++;
	
	if(cnt_interrupt % (1 * SECOND) == 0){
			
		if(r_time != 0){
			r_time -= 1;
		}
		 
		if(cnt_interrupt == (1 * MINUTE)){
			cnt_interrupt = 0;
		}
		 
	}
}