//RemainingTimeDisplay.c

#include "iodefine.h"
#include "RemainingTimeDisplay.h"

//10,4（待機秒数の候補）

void RTimeDisp_show_remaining_time(int remaining_time){
	
	static int cnt;
	
	int ten = remaining_time / 10;
	int one = remaining_time % 10;
	
	unsigned char ten_time = (0x00 | ten);
	unsigned char one_time = (0x00 | one);
	
	if(cnt%2 == 1){
		
		//1の位を表示
		RTimeDisp_show_one_time(one_time);
		
	}else if(cnt%2 == 0 && ten_time != 0){
		
		//10の位を表示
		RTimeDisp_show_ten_time(ten_time);

	}	
	
	cnt++;
}

void RTimeDisp_show_one_time(unsigned char one_time){
	
	//1の位を点灯
	PA.DR.BIT.B5 = 0;     /*PA5 を OFF*/
	PA.DR.BYTE = one_time;/*2. 1 の位の値を 4511 に出力*/
	PA.DR.BIT.B4 = 1;     /*3. PA4 を ON*/
	PA.DDR = 0xff;
	
	/*4.一定時間だけ待機(10ms)*/
}

void RTimeDisp_show_ten_time(unsigned char ten_time){

	//10の位を点灯
	PA.DR.BIT.B4 = 0;     /*5. PA4 を OFF*/
	PA.DR.BYTE = ten_time;/*6. 10 の位の値を 4511 に出力*/
	PA.DR.BIT.B5 = 1;     /*7. PA5 を ON*/
	PA.DDR = 0xff;  
	
	/*8.一定時間だけ待機(10ms)*/
}
