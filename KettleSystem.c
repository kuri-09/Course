/* KettleSystem.c */


/*E��off�̂Ƃ��͑҂���Ԃł���Aon�ɂ����u�ԂɎ��s�����*/
/*�����g�p�̃|�[�g�͓��͂ɂ���̂��}�i�[*/
/*0�������A1���ǂ�*/

/*���ΎQ��*/
#include "iodefine.h"

#include "KettleSystem.h"
#include "struct.h"

/*��ΎQ��*/
#include <stdio.h>
#include <string.h>

/*�v���g�^�C�v�錾*/
void init();
void init_sci1(unsigned char b_rate);
void charput(char c);

/*�\���̂̐錾*/
SYSTEM_CLASS SYSTEM;
INTERRUPT_CLASS INTERRUPT;
MANAGER_CLASS MANAGER;
ERROR_CLASS ERROR;


int main(void)
{
	
	//init
	init();
	init_sci1(80);//port�F9600 [baud]
	
	while(1){

		//�^�C�}���荞�݂Ŏ擾�����f�[�^���g��������
		Manager_interrupt(&SYSTEM, &INTERRUPT, &MANAGER);

		//check error
		Error_check_error(&SYSTEM, &INTERRUPT, &MANAGER, &ERROR);
		
		if(ERROR.FLAG.HAPPEN_HIGH_TEMP == HIGH || ERROR.FLAG.HAPPEN_UNABLE_TO_HEAT == HIGH)
		    break;
		
		/*--------------------------------- main ---------------------------------*/
		BoilFunction_boil(&SYSTEM, &INTERRUPT, &MANAGER);
		KeepWarmFunction_keep_warm(&SYSTEM, &INTERRUPT, &MANAGER);
		SupplyWaterFunction_supply_water(&SYSTEM, &INTERRUPT, &MANAGER);
		KitchenTimerFunction_timer(&SYSTEM, &INTERRUPT, &MANAGER);
		/*--------------------------------- main ---------------------------------*/

	}
	
    return 0;
}


void init(){
	
	/* AD�ϊ��ׂ̈̏����ݒ� */
	AD.ADCSR.BYTE = 0x40;
	
	/* DA�ϊ��ׂ̈̏����ݒ� */
	DA.DADR0 = 0x00;
	DA.DACR.BIT.DAOE0 = 1;
	DA.DADR1 = 0x00;
	DA.DACR.BIT.DAOE1 = 1;
	
	/* �q�[�^�d������������ */
	HeaterPower_turn_off();

	/* �u�U�[�C�l�[�u�������� */
	Buzzer_turn_off_enable();
	
	//�|�[�g�̐ݒ�
	P4.DDR = 0x00; //input(buttou)
	P6.DDR = 0xff;//output(buzzer, heaterpower)
	P9.DDR = 0x00; //input(cover)
	PA.DDR = 0xff;//output(timerdisplay)
	PB.DDR = 0xff;//output(lamp, waterlamp)

	/* LCD init */
	reset_lcd();
	//design_number(0, 5, 999);
}

//233

/*to use "printf"*/
void init_sci1(unsigned char b_rate)
{
	int i;
	SCI1.SCR.BYTE = 0; // �E��E��E��E��E�l�E��E� 0
    SCI1.SMR.BYTE = 0; // �E��E��E��E��E�l�E��E� 0
	SCI1.BRR = b_rate; // �E�r�E�b�E�g�E��E��E�[�E�g
	for (i = 0; i < 4000; i++); // �E�҂�
	SCI1.SCR.BYTE = 0x70; // �E��E�M�E��E��E�荞�݋��E�C�E��E��E��E�M�E��E��E��E�
	SCI1.SSR.BYTE; // �E�_�E�~�E�[�E��E��E�[�E�h
	SCI1.SSR.BYTE = 0x80; // �E�G�E��E��E�[�E�t�E��E��E�O�E�N�E��E��E�A
}

void charput(char c)
{
	while (!SCI1.SSR.BIT.TDRE); // �E��E��E�M�E��E�҂�
	SCI1.TDR = c;
	SCI1.SSR.BIT.TDRE = 0; // TDRE�E�N�E��E��E�A
}

/*
int i = 0;
double ad = 0;
const unsigned char data[] = "Keita_Igarashi";
int data_len = strlen(data);
*/