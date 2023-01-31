/*InternalInterrupt.c*/

/* header参照 */
#include "KettleSystem.h"
#include "macro.h"
#include "struct.h"

#include "iodefine.h"

#include <stdio.h>

/* プロトタイプ宣言 */
void isr_imia1();
void isr_imia2();
void isr_imia3();
void isr_adi();

/*構造体の宣言*/
extern SYSTEM_CLASS SYSTEM;
extern INTERRUPT_CLASS INTERRUPT;
extern MANAGER_CLASS MANAGER;
extern ERROR_CLASS ERROR;

//タイマ割り込み
void isr_imia1(){
	
	static int cnt;
	
	cnt++;
	
	/* 10ms */
	if(cnt%10 == 0){
		
		/* タイマ残り時間表示窓に残り時間を表示 */
		RTimeDisp_show_remaining_time((int)SYSTEM.KITCHEN.REMAINING_TIME);
		
		/* 100ms */
		if((cnt%100) == 0){
			
			/* ボタンの状態の取得 */
			INTERRUPT.INPUT.BUTTON_STATE = Button_get_button_state();
			
			/* ふたの状態の取得 */
			INTERRUPT.INPUT.COVER_STATE = Cover_get_cover_state();
			
			
			/* AD変換の開始 */
			isr_adi();
			AD.ADCSR.BIT.ADST = 1;
			
			/* DA変換の開始 */			
			INTERRUPT.FLAG.KEEP.DECIDE_PID_VALUE = HIGH;
						
			/* 1000ms */
			if(cnt == 1000){
				
				/* 水位の取得 */
				INTERRUPT.INPUT.WATER_LEVEL = WaterLevel_get_water_level();	
						
				cnt = 0;
			}
		}
	}
	
	//割り込みフラグのクリア
	if(ITU1.TSR.BIT.IMFA != 0){
		ITU1.TSR.BIT.IMFA = 0;
	}
}


//descaling and kitchen timer
void isr_imia2(){
	
	static int cnt_KitchenTimer;
	static int cnt_Descaling;
	static int second_KitchenTimer;
	static int second_Descaling;

	/****************************************** kitchen timer ******************************************/

	//KitchenTimer is start
	if(MANAGER.FLAG.KITCHEN.START_COUNT_DOWN == HIGH){

		cnt_KitchenTimer++;

	}else if(MANAGER.FLAG.KITCHEN.START_COUNT_DOWN == LOW){

		cnt_KitchenTimer = 0;
		second_KitchenTimer = 0;

	}
	
	//KitchenTimer is passed 1 second
	if(cnt_KitchenTimer == 1000){
		
		second_KitchenTimer += 1;

		if(second_KitchenTimer == 60){
			
			if(MANAGER.FLAG.KITCHEN.START_COUNT_DOWN == HIGH){
				
				if(SYSTEM.KITCHEN.REMAINING_TIME != 0){
					
					SYSTEM.KITCHEN.REMAINING_TIME -= 1;

				}

				//KitchenTimer is time out
				if(SYSTEM.KITCHEN.REMAINING_TIME == 0 && MANAGER.FLAG.KITCHEN.START_COUNT_DOWN == HIGH){
					
					INTERRUPT.FLAG.KITCHEN.TIME_OUT = HIGH;
				
				}
			}
			second_KitchenTimer = 0;
		}
		cnt_KitchenTimer = 0;

		
	}
	
	/****************************************** descaling ******************************************/

	//Descaling is start
	if(MANAGER.FLAG.BOIL.START_DESCALING == HIGH){

		cnt_Descaling++;
		
	}else if(MANAGER.FLAG.BOIL.START_DESCALING == LOW){
		
		cnt_Descaling = 0;
		second_Descaling = 0;
	}

	//Descaling is passed 1 second
	if(cnt_Descaling == 1000){
		
		second_Descaling += 1;

		if(second_Descaling == 180){
			
			if(MANAGER.FLAG.BOIL.START_DESCALING == HIGH){
				
				INTERRUPT.FLAG.BOIL.PASSED_THREE_MINUTES = HIGH;

			}
			second_Descaling = 0;
		}
		cnt_Descaling = 0;
	}
	
	/************************************************************************************/

	//割り込みフラグのクリア
	if(ITU2.TSR.BIT.IMFA != 0){
		ITU2.TSR.BIT.IMFA = 0;
	}
}

//error check
void isr_imia3(){
	
	static int cnt_ErrorCheck;
	static int cnt_RingBuzzer;
	static int second_ErrorCheck;
	static int second_RingBuzzer;

	/****************************************** check erro ******************************************/

	//buzzer is start
	if(ERROR.FLAG.START_CHECK_ERROR == HIGH){

		cnt_ErrorCheck++;

	}else if(ERROR.FLAG.START_CHECK_ERROR == LOW){

		cnt_ErrorCheck = 0;
		second_ErrorCheck = 0;

	}
	
	//ErrorCheck is passed 1 second
	if(cnt_ErrorCheck == 1000){
		
		second_ErrorCheck += 1;

		if(second_ErrorCheck == 60){
			
			if(ERROR.FLAG.START_CHECK_ERROR == HIGH){
				
				INTERRUPT.FLAG.ERROR.PASSED_ONE_MINUTE = HIGH;
			
			}
			second_ErrorCheck = 0;
		}
		cnt_ErrorCheck = 0;
	}

	/****************************************** ring buzzer ******************************************/

	//buzzer is start
	if(ERROR.FLAG.HAPPEN_HIGH_TEMP == HIGH || ERROR.FLAG.HAPPEN_UNABLE_TO_HEAT == HIGH){

		cnt_RingBuzzer++;

	}else{

		cnt_RingBuzzer = 0;
		second_RingBuzzer = 0;

	}
	
	//buzzer is passed 1 second
	if(cnt_RingBuzzer == 1000){
		
		second_RingBuzzer += 1;

		if(second_RingBuzzer == 30){
			
			if(ERROR.FLAG.HAPPEN_HIGH_TEMP == HIGH || ERROR.FLAG.HAPPEN_UNABLE_TO_HEAT == HIGH){
				
				INTERRUPT.FLAG.ERROR.PASSED_THIRTY_SECONDS = HIGH;
			
			}
			second_RingBuzzer = 0;
		}
		cnt_RingBuzzer = 0;
	}

	/************************************************************************************/

	//割り込みフラグのクリア
	if(ITU3.TSR.BIT.IMFA != 0){
		ITU3.TSR.BIT.IMFA = 0;
	}
}

/*AD変換（ローパスフィルターによる加工あり）*/
void isr_adi(){
	
	/*static */
	double ad_temp;
	
	INTERRUPT.INPUT.BEFORE_TEMP = INTERRUPT.INPUT.WATER_TEMP;
	
	ad_temp = (AD.ADDRA >> 6);
	ad_temp = (125.0 * ad_temp) /1024.0;
	ad_temp = (FILTER * INTERRUPT.INPUT.BEFORE_TEMP) + ((1 - FILTER) * ad_temp);

	INTERRUPT.INPUT.WATER_TEMP = ad_temp;
	INTERRUPT.INPUT.DISPLAY_WATER_TEMP = ad_temp + 0.5;
	
	//水温の変化を出力
	
	//割り込みフラグのクリア
	if(AD.ADCSR.BIT.ADF != 0){
		AD.ADCSR.BIT.ADF = 0;
	}
}