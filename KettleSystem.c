/* KettleSystem.c */
/*�����g�p�̃|�[�g�͓��͂ɂ���̂��}�i�[*/
/*E��off�̂Ƃ��͑҂���Ԃł���Aon�ɂ����u�ԂɎ��s�����*/
/*0�������A1���ǂ�*/

#include "iodefine.h"

#include "KettleSystem.h"

#include <stdio.h>
#include <string.h>

#define SECOND 1000

//�O���[�o���ϐ�
unsigned long int temp = 0x00;/*�^��T��*/
unsigned long int ad_temp = 0x00;


//int remaining_time = 0;
unsigned char water_level = 0x00;
unsigned char button_state = 0x00;
int cover_state = 0;

//�v���g�^�C�v�錾
void init();

//�ۉ��ݒ�̕ύX�Ƌ������̕ύX�i�\���̂̏�����������肭�����Ă��Ȃ��j
//�P�g���V�X�e������@�\�ɔ��ŁA�X�ɂ��̓����̊֐��ɔ�񂾂Ƃ��ɁA�����������Ă��Ȃ�

int main(void)
{
	int i = 0;
	unsigned int ad = 0;
	const unsigned char data[] = "Keita_Igarashi";
	int data_len = strlen(data);
	//int test_temp;
	
	//������
	init();
	
	//LCD�̏�����
	reset_lcd();
	
	/*������������ϊ��{�\��*/
	//design_number(0, 5, 999);

	//LCD�ɕۉ����[�h�̏o��
	//design_display_mode(98);
	
	
	while(1){
		
		temp = (125 * ad_temp) /1024;
		design_display_temp(temp);
		
		//�^�C�}���荞�݂ŃT���v�����O�����l����������
		Manager_interrupt(button_state, water_level, cover_state);

		
		/*���퓮��*/
		design_number(0, 5, ad_temp);
		design_number(0, 6, temp);
		design_number(0, 7, water_level);
		
	}
	
    return 0;
}

void init(){
	
	//AD�ϊ�
	/*
	AD.ADCSR.BIT.SCAN = 0;//���샂�[�h�̑I��(�P��)
	AD.ADCSR.BIT.ADIE = 1;//���荞�݂̋���
	AD.ADCSR.BIT.CH = 0x00;//�`�����l���̑I��
	*/
	AD.ADCSR.BYTE = 0x40;
	
	//DA�ϊ�
	//�q�[�^
	DA.DADR0 = 0x00;//�o�͏����l�̐ݒ�
	DA.DACR.BIT.DAOE0 = 1;//�o�͂̋���
	
	//�|���v
	DA.DADR1 = 0x00;
	DA.DACR.BIT.DAOE1 = 1;
	
	//�u�U�[�E�q�[�^�d��
	P6.DDR = 0xff;//�����G���[�Ȃ��Ȃ�
	HeaterPower_turn_off();
}