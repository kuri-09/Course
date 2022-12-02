/* KettleSystem.c */
/*�����g�p�̃|�[�g�͓��͂ɂ���̂��}�i�[*/
/*E��off�̂Ƃ��͑҂���Ԃł���Aon�ɂ����u�ԂɎ��s�����*/
/*0�������A1���ǂ�*/

#include "iodefine.h"

#include "KettleSystem.h"

#include <stdio.h>
#include <string.h>

#define SECOND 1000

//�ۉ��ݒ�̕ύX�Ƌ������̕ύX�i�\���̂̏�����������肭�����Ă��Ȃ��j
//�P�g���V�X�e������@�\�ɔ��ŁA�X�ɂ��̓����̊֐��ɔ�񂾂Ƃ��ɁA�����������Ă��Ȃ�

int main(void)
{
	int i = 0;
	const unsigned char data[] = "Keita_Igarashi";
	int data_len = strlen(data);
	
	//LCD�̏�����
	reset_lcd();
	
	/*�����\��*/
	design_char(60, 0, 'A');
	
	/*������\��*/
	design_string(60, 3, data, data_len);
	
	/*������������ϊ��{�\��*/
	design_number(0, 5, 999);
	wait_ms(SECOND);
	
	/*�摜�\���֐�*/
	design_image();
	wait_ms(SECOND/2);
	
	reset_lcd();
	
	//LCD�ɏo��
	design_display_mode(98);
	design_display_temp(100);
	wait_ms(SECOND/2);
	
	
	while(1){
			
			for(i=0; i<101; i++){
				
				design_display_temp(i);
				wait_ms(SECOND/2);
			}
			
	}
	
    return 0;
}






