/*InternalInterrupt.c*/

/*header�ǂݍ���*/
#include "KettleSystem.h"
//#include "Manager.h"

#include "iodefine.h"
//#include <machine.h>

/*�v���g�^�C�v�錾*/
void isr_imia1();
void isr_adi();

/*extern�錾*/
extern int temp;


extern int ad_temp;
extern int remaining_time;
extern int cover_state;
extern unsigned char water_level;
extern unsigned char button_state;
extern int time_out;
//int remaining_time = 0;

extern heat heat_state;

//16�r�b�g��
void isr_imia1(){
	
	static int cnt;
	static btn btn_type;
	
	cnt++;
	
	//10ms���ɏ������s��
	if(cnt%10 == 0){
		
		/*�^�C�}���荞�݁F���ԕ\��*/
		RTimeDisp_show_remaining_time(remaining_time);
		
		if((cnt%100) == 0){
			
			//�{�^���̏�ԓǂݍ���
			button_state = Button_get_botan_state();
			
			//�ӂ��̏�ԓǂݍ���
			cover_state = Cover_get_cover_state();
			
			if(cnt == 1000){
				
				//���ʂ̏�ԓǂݍ���
				water_level = WaterLevel_get_water_level();
				
				//AD�ϊ��̊J�n
				isr_adi();//�ǂݎ��
				AD.ADCSR.BIT.ADST = 1;//�ϊ��̊J�n
				
				/*-----------------------------��������-----------------------------------*/
				
				//DA�ϊ��̊J�n
				
				//����(�ڕW���x ON/OFF ����)
				if(heat_state == boiling){
					if(temp < 100){
						
					    DA.DADR0 = 0xff;//�o�͒l�̐ݒ�
						HeaterPower_turn_on();
						
				    }
				}
				
				if(temp >= 100){
					
					DA.DADR0 = 0x00;//�o�͒l�̐ݒ�
					HeaterPower_turn_off();
					heat_state = off;
					
				}
				//DA.DACR.BIT.DAOE0 = 1;//�ϊ��̊J�n
				
				
				/*------------------------------�����܂�----------------------------------*/
				
				//��b�J�E���g
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
	
	//���荞�݃t���O�̃N���A
	if(ITU1.TSR.BIT.IMFA != 0){//��Ԃ̃��[�h

		ITU1.TSR.BIT.IMFA = 0;

	}
}


//16�r�b�g��
//void isr_imia2(){
	
	
	
	/*���荞�݃t���O�̃N���A*/
	/*if(ITU2.TSR.BIT.IMFA != 0){//��Ԃ̃��[�h

		ITU2.TSR.BIT.IMFA = 0;

	}
}*/

/*�ϊ���̐��l�̓ǂݎ��*/
void isr_adi(){
	
	ad_temp = (AD.ADDRA >> 6);
	
	//���荞�݃t���O�̃N���A
	if(AD.ADCSR.BIT.ADF != 0){//��Ԃ̃��[�h

		AD.ADCSR.BIT.ADF = 0;

	}
}