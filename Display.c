//Display.c

#include "iodefine.h"
#include "Display.h"

#include "font.h"
#include "image.h"

#define WAIT 300000
#define ANIME 300000000
#define NUMBER 32
#define MODE 64
#define PAGE 8

#define SECOND 1000

#include <stdio.h>
#include <string.h>
#include <machine.h>

/*�^�C�}�������֐�*/
void timer_init()
{
	//LCD
	ITU.TSTR.BIT.STR0 = 0;    /*1. �^�C�}�J�E���g�̒�~*/  
	ITU0.TCR.BIT.CCLR = 1;    /*2. �^�C�}�̗��p���@�̐ݒ�*/	
	ITU0.TCR.BIT.CKEG = 0;	
	ITU0.TCR.BIT.TPSC = 0x03;
	ITU0.TIOR.BIT.IOA = 0;    /*3. �W�F�l�������W�X�^�̗��p���@�̐ݒ�*/		
	ITU0.GRA = 3125;          /*4. �W�F�l�������W�X�^�̒l�̐ݒ�*/	
	//�Ȃ�                    /*5. ���荞�݂̋���*/
	
	//7 segment
	ITU.TSTR.BIT.STR1 = 0;    /*1. �^�C�}�J�E���g�̒�~*/  
	ITU1.TCR.BIT.CCLR = 1;    /*2. �^�C�}�̗��p���@�̐ݒ�*/	
	ITU1.TCR.BIT.CKEG = 0;	
	ITU1.TCR.BIT.TPSC = 0x03;
	ITU1.TIOR.BIT.IOA = 0;    /*3. �W�F�l�������W�X�^�̗��p���@�̐ݒ�*/		
	ITU1.GRA = 3125;          /*4. �W�F�l�������W�X�^�̒l�̐ݒ�*/
	ITU1.TIER.BIT.IMIEA = 1;  /*5. ���荞�݂̋���*/
	
	//descaling and kitchen timer
	ITU.TSTR.BIT.STR2 = 0;    /*1. �^�C�}�J�E���g�̒�~*/  
	ITU2.TCR.BIT.CCLR = 1;    /*2. �^�C�}�̗��p���@�̐ݒ�*/	
	ITU2.TCR.BIT.CKEG = 0;	
	ITU2.TCR.BIT.TPSC = 0x03;
	ITU2.TIOR.BIT.IOA = 0;    /*3. �W�F�l�������W�X�^�̗��p���@�̐ݒ�*/		
	ITU2.GRA = 3125;          /*4. �W�F�l�������W�X�^�̒l�̐ݒ�*/
	ITU2.TIER.BIT.IMIEA = 1;  /*5. ���荞�݂̋���*/

	//error check
	ITU.TSTR.BIT.STR3= 0;    /*1. �^�C�}�J�E���g�̒�~*/  
	ITU3.TCR.BIT.CCLR = 1;    /*2. �^�C�}�̗��p���@�̐ݒ�*/	
	ITU3.TCR.BIT.CKEG = 0;	
	ITU3.TCR.BIT.TPSC = 0x03;
	ITU3.TIOR.BIT.IOA = 0;    /*3. �W�F�l�������W�X�^�̗��p���@�̐ݒ�*/		
	ITU3.GRA = 3125;          /*4. �W�F�l�������W�X�^�̒l�̐ݒ�*/
	ITU3.TIER.BIT.IMIEA = 1;  /*5. ���荞�݂̋���*/
	
	//�ӂ�
	INTC.ISCR.BIT.IRQ4SC = 1; /*1. ���x���Z���X�^����������̑I��*/
	INTC.IER.BIT.IRQ4E = 1;   /*2. ���荞�݂̋���*/

	
	//�S���荞�݂̋���
	set_imask_ccr(0);
	
	ITU.TSTR.BIT.STR1 = 1;    /*6. �^�C�}�J�E���g�̊J�n*/
	ITU.TSTR.BIT.STR2 = 1;    /*6. �^�C�}�J�E���g�̊J�n*/
	ITU.TSTR.BIT.STR3 = 1;    /*6. �^�C�}�J�E���g�̊J�n*/
	
}



/* 1 [ms] �ҋ@�֐�*/ 
void wait1_ms()
{
	ITU.TSTR.BIT.STR0 = 1;        /*1. �^�C�}�J�E���g�̊J�n*/
	while(ITU0.TSR.BIT.IMFA != 1);/*2. �t���O�̗����オ��̑ҋ@*/
	ITU0.TSR.BIT.IMFA = 0;        /*3. �t���O�̃��Z�b�g*/
	ITU.TSTR.BIT.STR0 = 0;        /*4. �^�C�}�J�E���g�̒�~*/
}

/*�� n [ms] �ҋ@�֐� */
void wait_ms(int ms)
{
	int cnt = 0;
	while(cnt < ms){
		wait1_ms();
		cnt++;
	}
}

/*240 [ns] �ҋ@�֐�*/
void wait_240nsec()
{
	nop(); /* Non operation */
	nop(); /* Non operation */
	nop(); /* Non operation */
}

/*LCD �ǂݍ��݊֐�*//*�O����������1���ǂݍ���*/
unsigned char read_lcd(int rs, int cs)
{	
	unsigned char data;
	
	P3.DR.BIT.B2 = 0;    /* 1. E �� OFF*/
	P3.DR.BIT.B1 = 1;    /* 2. R/W �� ON*/
	P3.DR.BIT.B4 = 0;    /* 3. CS1(��), CS2(�E)�̗��҂�oFF�C�w�߂��������� ON*/
	P3.DR.BIT.B5 = 0;
	
	if(cs == 1)
		P3.DR.BIT.B4 = 1;/*��*/
		
	else if(cs == 2)
		P3.DR.BIT.B5 = 1;/*�E*/
		
	
	P3.DR.BIT.B0 = rs;   /* 4. RS ��ݒ�*//*1*/
	wait_240nsec();      /* 5. 240 [ns] �ҋ@*/
	P3.DR.BIT.B2 = 1;    /* 6. E �� ON*/
	wait_240nsec();      /* 7. 480 [ns] �ҋ@ �� 240 [ns] �ҋ@�~ 2 ��*/
	wait_240nsec();	
	
	P2.DDR = 0x00;       /* 8. DB0 �` 7 ��ǂݍ��� ���|�[�g����͂ɐݒ�*/
	data = P2.DR.BYTE;

	P3.DR.BIT.B2 = 0;    /* 9. E �� OFF*/
	P3.DR.BIT.B2 = 1;    /*10. E �� ON*/
	
	return data;
}

/*BF �`�F�b�N�֐�*/
void check_bf(int cs)
{	
	unsigned char data;
	
	do{
		data = read_lcd(0, cs);
	} while ((data & 0x80) != 0);
}


/*LCD �������݊֐�*/
void write_lcd(int rs, int cs, unsigned char data)
{	
	P3.DR.BIT.B2 = 0; /*1. E �� OFF*/
	P3.DR.BIT.B1 = 0; /*2. R/W �� OFF*/
	P3.DR.BIT.B4 = 0; /*3. CS1(��), CS2(�E)�̗��҂� OFF�C�w�߂��������� ON*/
	P3.DR.BIT.B5 = 0;
	
	if(cs == 1)
		P3.DR.BIT.B4 = 1;/*��*/
		
	else if(cs == 2)
		P3.DR.BIT.B5 = 1;/*�E*/
		
	P3.DR.BIT.B0 = rs;/*4. RS ��ݒ�*//*��1*/
	wait_240nsec();   /*5. 240 [ns] �ҋ@*/
	P3.DR.BIT.B2 = 1; /*6. E �� ON*/
	
	P2.DR.BYTE = data;/*7. DB0 ? 7 ��ݒ� ���|�[�g���o�͂ɐݒ�*/
	P2.DDR = 0xff;
	
	wait_240nsec();   /*8. 480 [ns] �ҋ@ �� 240 [ns] �ҋ@�~ 2 ��*/
	wait_240nsec();
	P3.DR.BIT.B2 = 0; /*9. E �� OFF*/
	P3.DR.BIT.B2 = 1; /*10. E �� ON*/
	
	check_bf(cs);
}

/*LCD �������֐�*/
void reset_lcd()
{	
	int i=0;
	int j=0;
	int cs;
	
	//init();
	
	P3.DDR = 0xff;    /*�|�[�g 3 �̊e�r�b�g��K�v�ɉ����ďo�͂ɐݒ�*/
	P3.DR.BIT.B2 = 1; /*E �� ON*/
	P3.DR.BIT.B6 = 0; /*#RST �� OFF*//*�A�N�e�B�u���[*/
	timer_init();     /*tRS = 1 [��s] ��ҋ@*/
	
	P3.DR.BIT.B6 = 1; /*#RST �� ON*/
	wait_ms(30);      /*�^�C�}���g���� 30 [ms] ���v��*/
		
	write_lcd(0, 1, 0xc0);/*set display start line to first line*/
	write_lcd(0, 2, 0xc0);	
	
	write_lcd(0, 1, 0x3f);/*set display on*/
	write_lcd(0, 2, 0x3f);
	
	for(j= 0; j<=7; j++){/*���N���A*/
		for(i=0; i<64; i++){
			point_lcd(i, j);	
			write_lcd(1, 1, 0x00);
		}
	}
	
	for(j= 0; j<=7; j++){/*�E�N���A*/
		for(i=64; i<128; i++){
			point_lcd(i, j);
			write_lcd(1, 2, 0x00);
		}
	}
}

/*�`����W�w��֐�*/
void point_lcd(int x, int y)
{	
	int cs = 0;	
	int local_yl = x;
	int local_yr = x - 64;
	int local_x = y;
	
	if(0<=x & x<64)
		cs = 1;
		
	else if(64<=x & x<128)
		cs = 2;
		
	/*X*/
	write_lcd(0, cs,  0xb8 | local_x);
	
	/*Y*/
	if(0 <= x && x <= 63)
		write_lcd(0, cs, 0x40 | local_yl);
		
	else if(64 <= x && x <= 127)
		write_lcd(0, cs, 0x40 | local_yr);
}


/*�c8�h�b�g�̕`��֐�*/
void design_lcd(int x, int y, unsigned char data)
{	
	int cs;
	
	if(0<=x && x<64)
		cs = 1;
		
	else if(64<=x && x<128)
		cs = 2;
		
	point_lcd(x, y);
	/*write date*/		
	write_lcd(1, cs, data);
}

/*�����\�����W�w��֐�*/
int point_char(int x, int page)
{	                         
	int cs = 0;	
	int global_xl = x;
	int global_xr = x;
	int global_y = page;
	
	if(0<=x && x<=56)
		cs = 1;
		
	else if(64<=x && x<=120)
		cs = 2;

	else if(57<=x && x<64)
		cs = 3;
		
	else if(121<=x && x<128)
		cs = 4;
		

	if(0<=x && x<64)
		point_lcd(global_xl, global_y);
	
	else if(64<=x && x<128)
		point_lcd(global_xr, global_y);
		
	return cs;
}

/*�����\���֐�*/
void design_char(int x, int page, unsigned char data)
{		
	int cs;
	int i;
	int left = 63 - x;
	int right = 127 - x;
	
	cs = point_char(x, page);
	
	/*write date*/
	if(cs == 1 || cs == 2){
		for(i=0; i<=7; i++){
			write_lcd(1, cs, font[data][i]);
		}
	}
	else if(cs == 3){
		for(i=0; i<=left; i++){
			write_lcd(1, 1, font[data][i]);
		}
		cs = point_char(64, page);
		for(i=left+1; i<=7; i++){
			write_lcd(1, cs, font[data][i]);
		}
	}
	else if(cs == 4){
		for(i=0; i<=right; i++){
			write_lcd(1, 2, font[data][i]);
		}
		cs = point_char(0, page);
		for(i=right+1; i<=7; i++){
			write_lcd(1, cs, font[data][i]);
		}
	}
	
}

/*������\���֐�*/
void design_string(int x, int page, unsigned char *data_cnt, int data_len)
{	
	int cs;
	int i,j;	
	
	unsigned char data[80];
	unsigned char str[80];
	
	int word_len = data_len * 8;
	
	int left,right;
	int range = x + word_len -1;
	
	strcpy(data,data_cnt);/*�����̃R�s�[*/
	
	if(range <= 255){
		for(j=0; j<data_len; j++){
			left = 63 - x;
			right = 127 - x;
			cs = point_char(x, page);
			if(cs == 1 || cs == 2){
				for(i=0; i<=7; i++){
					write_lcd(1, cs, font[data[j]][i]);
				}
			x = x + 8;
			}
			else if(cs == 3){
				for(i=0; i<=left; i++){
					write_lcd(1, 1, font[data[j]][i]);
				}
				cs = point_char(64, page);
				for(i=left+1; i<=7; i++){
					write_lcd(1, cs, font[data[j]][i]);
				}
			x = x + 8;
			}
			else if(cs == 4){
				for(i=0; i<=right; i++){
					write_lcd(1, 2, font[data[j]][i]);
				}
				cs = point_char(0, page);
				for(i=right+1; i<=7; i++){
					write_lcd(1, cs, font[data[j]][i]);
				}
			x = x + 7 - 127;
			}
		}
	}	
}

/*������������ϊ��{�\��*/
void design_number(int x, int page, int data_num)
{
	int i, data_len;	
	/*3��*/
	unsigned char str[14];
	
	sprintf(str,"%d", data_num);
	data_len = strlen(str);
	
	design_string(x, page, str, data_len);
}

void image0_design()
{
	
	int cs;
	int x = 0;
	int page = 0;	
	
	for(page=0; page<8; page++){
		for(x=0; x<128; x++){
			if(x < 64){
				point_lcd(x, page);
				write_lcd(1, 1, image0_data[page][x]);
			}
			if(x >= 64){
				point_lcd(x, page);
				write_lcd(1, 2, image0_data[page][x]);
			}
		}
	}			
}

/*�摜�\���֐�*/
void design_image()
{	
	long int i;
	int j;
	int cnt = 0;
	const unsigned char data1[] = "Loading";
	const unsigned char data2[] = "L";
	const unsigned char data3[] = "Lo";
	const unsigned char data4[] = "Loa";
	const unsigned char data5[] = "Load";
	const unsigned char data6[] = "Loadi";
	const unsigned char data7[] = "Loadin";
	const unsigned char data9[] = "Thank";
	const unsigned char data10[] = "you";
	const unsigned char data11[] = "for";
	const unsigned char data12[] = "using";
	
	image0_design();
	
	for (j = 0; j < 10; j++){
		for (i = 0; i < WAIT; i++);	
		design_string(0, 0, data9, 6);
	}
	for (j = 0; j < 10; j++){
		for (i = 0; i < WAIT; i++);		
		design_string(0, 1, data10, 4);			
	}
	for (j = 0; j < 10; j++){
		for (i = 0; i < WAIT; i++);	
		design_string(0, 2, data11, 4);	
	}
	for (j = 0; j < 20; j++){
		for (i = 0; i < WAIT; i++);		
		design_string(0, 3, data12, 6);	
	}
	
	for(cnt = 0; cnt < 1; cnt++){
		for (j = 0; j < 2; j++){
			for (i = 0; i < WAIT; i++);
			image1_design();
			design_string(64, 7, data1, 8);
		}
		for (j = 0; j < 2; j++){
			for (i = 0; i < WAIT; i++);
			image2_design();
			design_string(64, 7, data2, 2);	
		}
		for (j = 0; j < 2; j++){	
			for (i = 0; i < WAIT; i++);
			image3_design();
			design_string(64, 7, data3, 3);
		}
		for (j = 0; j < 2; j++){
			for (i = 0; i < WAIT; i++);
			image4_design();
			design_string(64, 7, data4, 4);
		}
		for (j = 0; j < 2; j++){	
			for (i = 0; i < WAIT; i++);
			image5_design();
			design_string(64, 7, data5, 5);
		}
		for (j = 0; j < 2; j++){
			for (i = 0; i < WAIT; i++);
			image6_design();
			design_string(64, 7, data6, 6);
		}
		for (j = 0; j < 2; j++){
			for (i = 0; i < WAIT; i++);
			image7_design();
			design_string(64, 7, data7, 7);
		}
	}
}
 
/*LED����*/
void LCD_light()
{
	long int i;

    P9.DDR = 0x01;                 /* P9��0 ���o�͂ɐݒ� */

    while (1) {
        for (i = 0; i < WAIT; i++);
        P9.DR.BYTE = 0x00;           /* LED �����i�o�C�g�P�ʑ���j */

        for (i = 0; i < WAIT; i++);
        P9.DR.BIT.B0 = 1;            /* LED �_���i�r�b�g�P�ʑ���j */
	}
}


void design_display_char(int x, int page, unsigned char *data_cnt, int data_len)
{	
	int cs;
	int i,j;	
	
	unsigned char data[80];
	unsigned char str[80];
	
	int word_len = data_len * 8;
	
	int left,right;
	int range = x + word_len -1;
	
	strcpy(data,data_cnt);/*�����̃R�s�[*/
	
	if(range <= 255){
		for(j=0; j<data_len; j++){
			left = 63 - x;
			right = 127 - x;
			cs = point_char(x, page);
			if(cs == 1 || cs == 2){
				for(i=0; i<=7; i++){
					write_lcd(1, cs, font[data[j]][i]);
				}
			x = x + 8;
			}
			else if(cs == 3){
				for(i=0; i<=left; i++){
					write_lcd(1, 1, font[data[j]][i]);
				}
				cs = point_char(64, page);
				for(i=left+1; i<=7; i++){
					write_lcd(1, cs, font[data[j]][i]);
				}
			x = x + 8;
			}
			else if(cs == 4){
				for(i=0; i<=right; i++){
					write_lcd(1, 2, font[data[j]][i]);
				}
				cs = point_char(0, page);
				for(i=right+1; i<=7; i++){
					write_lcd(1, cs, font[data[j]][i]);
				}
			x = x + 7 - 127;
			}
		}
	}	
}

int point_image(int x, int page)
{	                         
	int cs = 0;	
	int global_xl = x;
	int global_xr = x;
	int global_y = page;
	
	if(0<=x && x<=64)
		cs = 1;
		
	else if(64<=x && x<=128)
		cs = 2;
	

	if(0<=x && x<64)
		point_lcd(global_xl, global_y);
	
	else if(64<=x && x<128)
		point_lcd(global_xr, global_y);
		
	return cs;
}

/*�f�B�X�v���C�S��ʕ\��*/
void design_display_all(int water_temp, int target_temp)
{	

	int cnt = 0;
	int i = 0;	
		
	if(target_temp == 0){
		//for (water_temp = 0; water_temp < 101; water_temp++){
			design_display_temp(water_temp);
			wait_ms(SECOND/50);
			//cnt++;
	    //}
	}else{
		//for (water_temp = 0; water_temp < 10; water_temp++){
			design_display_temp(water_temp);
			design_display_mode(target_temp);
			wait_ms(SECOND/50);
			//cnt++;
	    //}
	}
}

