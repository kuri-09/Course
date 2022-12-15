/*InternalInterrupt.c*/

/*header読み込み*/
#include "KettleSystem.h"
//#include "Manager.h"

#include "iodefine.h"
//#include <machine.h>

/*プロトタイプ宣言*/
void isr_imia1();
void isr_adi();

/*extern宣言*/
extern int temp;


extern int ad_temp;
extern int remaining_time;
extern int cover_state;
extern unsigned char water_level;
extern unsigned char button_state;
extern int time_out;
//int remaining_time = 0;

extern heat heat_state;

//16ビット幅
void isr_imia1(){
	
	static int cnt;
	static btn btn_type;
	
	cnt++;
	
	//10ms毎に処理を行う
	if(cnt%10 == 0){
		
		/*タイマ割り込み：時間表示*/
		RTimeDisp_show_remaining_time(remaining_time);
		
		if((cnt%100) == 0){
			
			//ボタンの状態読み込み
			button_state = Button_get_botan_state();
			
			//ふたの状態読み込み
			cover_state = Cover_get_cover_state();
			
			if(cnt == 1000){
				
				//水位の状態読み込み
				water_level = WaterLevel_get_water_level();
				
				//AD変換の開始
				isr_adi();//読み取り
				AD.ADCSR.BIT.ADST = 1;//変換の開始
				
				/*-----------------------------ここから-----------------------------------*/
				
				//DA変換の開始
				
				//沸騰(目標温度 ON/OFF 方式)
				if(heat_state == boiling){
					if(temp < 100){
						
					    DA.DADR0 = 0xff;//出力値の設定
						HeaterPower_turn_on();
						
				    }
				}
				
				if(temp >= 100){
					
					DA.DADR0 = 0x00;//出力値の設定
					HeaterPower_turn_off();
					heat_state = off;
					
				}
				//DA.DACR.BIT.DAOE0 = 1;//変換の開始
				
				
				/*------------------------------ここまで----------------------------------*/
				
				//一秒カウント
				if(remaining_time != 0){
					remaining_time -= 1;
					
					if(remaining_time == 0){
						time_out = 1;
					}
					
				}
				cnt = 0;
			}
		}
	}
	
	//割り込みフラグのクリア
	if(ITU1.TSR.BIT.IMFA != 0){//状態のリード

		ITU1.TSR.BIT.IMFA = 0;

	}
}


//16ビット幅
//void isr_imia2(){
	
	
	
	/*割り込みフラグのクリア*/
	/*if(ITU2.TSR.BIT.IMFA != 0){//状態のリード

		ITU2.TSR.BIT.IMFA = 0;

	}
}*/

/*変換後の数値の読み取り*/
void isr_adi(){
	
	ad_temp = (AD.ADDRA >> 6);
	
	//割り込みフラグのクリア
	if(AD.ADCSR.BIT.ADF != 0){//状態のリード

		AD.ADCSR.BIT.ADF = 0;

	}
}