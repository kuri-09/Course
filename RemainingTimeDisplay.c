//RemainingTimeDisplay.c

#include "iodefine.h"
#include "RemainingTimeDisplay.h"

//10,4�i�ҋ@�b���̌��j

void RTimeDisp_show_remaining_time(int remaining_time){
	
	static int cnt;
	
	int ten = remaining_time / 10;
	int one = remaining_time % 10;
	
	unsigned char ten_time = (0x00 | ten);
	unsigned char one_time = (0x00 | one);
	
	if(cnt%2 == 1){
		
		//1�̈ʂ�\��
		RTimeDisp_show_one_time(one_time);
		
	}else if(cnt%2 == 0 && ten_time != 0){
		
		//10�̈ʂ�\��
		RTimeDisp_show_ten_time(ten_time);

	}	
	
	cnt++;
}

void RTimeDisp_show_one_time(unsigned char one_time){
	
	//1�̈ʂ�_��
	PA.DR.BIT.B5 = 0;     /*PA5 �� OFF*/
	PA.DR.BYTE = one_time;/*2. 1 �̈ʂ̒l�� 4511 �ɏo��*/
	PA.DR.BIT.B4 = 1;     /*3. PA4 �� ON*/
	PA.DDR = 0xff;
	
	/*4.��莞�Ԃ����ҋ@(10ms)*/
}

void RTimeDisp_show_ten_time(unsigned char ten_time){

	//10�̈ʂ�_��
	PA.DR.BIT.B4 = 0;     /*5. PA4 �� OFF*/
	PA.DR.BYTE = ten_time;/*6. 10 �̈ʂ̒l�� 4511 �ɏo��*/
	PA.DR.BIT.B5 = 1;     /*7. PA5 �� ON*/
	PA.DDR = 0xff;  
	
	/*8.��莞�Ԃ����ҋ@(10ms)*/
}
