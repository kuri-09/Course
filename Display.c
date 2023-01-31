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

/*タイマ初期化関数*/
void timer_init()
{
	//LCD
	ITU.TSTR.BIT.STR0 = 0;    /*1. タイマカウントの停止*/  
	ITU0.TCR.BIT.CCLR = 1;    /*2. タイマの利用方法の設定*/	
	ITU0.TCR.BIT.CKEG = 0;	
	ITU0.TCR.BIT.TPSC = 0x03;
	ITU0.TIOR.BIT.IOA = 0;    /*3. ジェネラルレジスタの利用方法の設定*/		
	ITU0.GRA = 3125;          /*4. ジェネラルレジスタの値の設定*/	
	//なし                    /*5. 割り込みの許可*/
	
	//7 segment
	ITU.TSTR.BIT.STR1 = 0;    /*1. タイマカウントの停止*/  
	ITU1.TCR.BIT.CCLR = 1;    /*2. タイマの利用方法の設定*/	
	ITU1.TCR.BIT.CKEG = 0;	
	ITU1.TCR.BIT.TPSC = 0x03;
	ITU1.TIOR.BIT.IOA = 0;    /*3. ジェネラルレジスタの利用方法の設定*/		
	ITU1.GRA = 3125;          /*4. ジェネラルレジスタの値の設定*/
	ITU1.TIER.BIT.IMIEA = 1;  /*5. 割り込みの許可*/
	
	//descaling and kitchen timer
	ITU.TSTR.BIT.STR2 = 0;    /*1. タイマカウントの停止*/  
	ITU2.TCR.BIT.CCLR = 1;    /*2. タイマの利用方法の設定*/	
	ITU2.TCR.BIT.CKEG = 0;	
	ITU2.TCR.BIT.TPSC = 0x03;
	ITU2.TIOR.BIT.IOA = 0;    /*3. ジェネラルレジスタの利用方法の設定*/		
	ITU2.GRA = 3125;          /*4. ジェネラルレジスタの値の設定*/
	ITU2.TIER.BIT.IMIEA = 1;  /*5. 割り込みの許可*/

	//error check
	ITU.TSTR.BIT.STR3= 0;    /*1. タイマカウントの停止*/  
	ITU3.TCR.BIT.CCLR = 1;    /*2. タイマの利用方法の設定*/	
	ITU3.TCR.BIT.CKEG = 0;	
	ITU3.TCR.BIT.TPSC = 0x03;
	ITU3.TIOR.BIT.IOA = 0;    /*3. ジェネラルレジスタの利用方法の設定*/		
	ITU3.GRA = 3125;          /*4. ジェネラルレジスタの値の設定*/
	ITU3.TIER.BIT.IMIEA = 1;  /*5. 割り込みの許可*/
	
	//ふた
	INTC.ISCR.BIT.IRQ4SC = 1; /*1. レベルセンス／立ち下がりの選択*/
	INTC.IER.BIT.IRQ4E = 1;   /*2. 割り込みの許可*/

	
	//全割り込みの許可
	set_imask_ccr(0);
	
	ITU.TSTR.BIT.STR1 = 1;    /*6. タイマカウントの開始*/
	ITU.TSTR.BIT.STR2 = 1;    /*6. タイマカウントの開始*/
	ITU.TSTR.BIT.STR3 = 1;    /*6. タイマカウントの開始*/
	
}



/* 1 [ms] 待機関数*/ 
void wait1_ms()
{
	ITU.TSTR.BIT.STR0 = 1;        /*1. タイマカウントの開始*/
	while(ITU0.TSR.BIT.IMFA != 1);/*2. フラグの立ち上がりの待機*/
	ITU0.TSR.BIT.IMFA = 0;        /*3. フラグのリセット*/
	ITU.TSTR.BIT.STR0 = 0;        /*4. タイマカウントの停止*/
}

/*⇒ n [ms] 待機関数 */
void wait_ms(int ms)
{
	int cnt = 0;
	while(cnt < ms){
		wait1_ms();
		cnt++;
	}
}

/*240 [ns] 待機関数*/
void wait_240nsec()
{
	nop(); /* Non operation */
	nop(); /* Non operation */
	nop(); /* Non operation */
}

/*LCD 読み込み関数*//*０が書き込み1が読み込み*/
unsigned char read_lcd(int rs, int cs)
{	
	unsigned char data;
	
	P3.DR.BIT.B2 = 0;    /* 1. E を OFF*/
	P3.DR.BIT.B1 = 1;    /* 2. R/W を ON*/
	P3.DR.BIT.B4 = 0;    /* 3. CS1(左), CS2(右)の両者をoFF，指令したい方を ON*/
	P3.DR.BIT.B5 = 0;
	
	if(cs == 1)
		P3.DR.BIT.B4 = 1;/*左*/
		
	else if(cs == 2)
		P3.DR.BIT.B5 = 1;/*右*/
		
	
	P3.DR.BIT.B0 = rs;   /* 4. RS を設定*//*1*/
	wait_240nsec();      /* 5. 240 [ns] 待機*/
	P3.DR.BIT.B2 = 1;    /* 6. E を ON*/
	wait_240nsec();      /* 7. 480 [ns] 待機 ※ 240 [ns] 待機× 2 回*/
	wait_240nsec();	
	
	P2.DDR = 0x00;       /* 8. DB0 ～ 7 を読み込み ※ポートを入力に設定*/
	data = P2.DR.BYTE;

	P3.DR.BIT.B2 = 0;    /* 9. E を OFF*/
	P3.DR.BIT.B2 = 1;    /*10. E を ON*/
	
	return data;
}

/*BF チェック関数*/
void check_bf(int cs)
{	
	unsigned char data;
	
	do{
		data = read_lcd(0, cs);
	} while ((data & 0x80) != 0);
}


/*LCD 書き込み関数*/
void write_lcd(int rs, int cs, unsigned char data)
{	
	P3.DR.BIT.B2 = 0; /*1. E を OFF*/
	P3.DR.BIT.B1 = 0; /*2. R/W を OFF*/
	P3.DR.BIT.B4 = 0; /*3. CS1(左), CS2(右)の両者を OFF，指令したい方を ON*/
	P3.DR.BIT.B5 = 0;
	
	if(cs == 1)
		P3.DR.BIT.B4 = 1;/*左*/
		
	else if(cs == 2)
		P3.DR.BIT.B5 = 1;/*右*/
		
	P3.DR.BIT.B0 = rs;/*4. RS を設定*//*可変1*/
	wait_240nsec();   /*5. 240 [ns] 待機*/
	P3.DR.BIT.B2 = 1; /*6. E を ON*/
	
	P2.DR.BYTE = data;/*7. DB0 ? 7 を設定 ※ポートを出力に設定*/
	P2.DDR = 0xff;
	
	wait_240nsec();   /*8. 480 [ns] 待機 ※ 240 [ns] 待機× 2 回*/
	wait_240nsec();
	P3.DR.BIT.B2 = 0; /*9. E を OFF*/
	P3.DR.BIT.B2 = 1; /*10. E を ON*/
	
	check_bf(cs);
}

/*LCD 初期化関数*/
void reset_lcd()
{	
	int i=0;
	int j=0;
	int cs;
	
	//init();
	
	P3.DDR = 0xff;    /*ポート 3 の各ビットを必要に応じて出力に設定*/
	P3.DR.BIT.B2 = 1; /*E を ON*/
	P3.DR.BIT.B6 = 0; /*#RST を OFF*//*アクティブロー*/
	timer_init();     /*tRS = 1 [μs] を待機*/
	
	P3.DR.BIT.B6 = 1; /*#RST を ON*/
	wait_ms(30);      /*タイマを使って 30 [ms] を計測*/
		
	write_lcd(0, 1, 0xc0);/*set display start line to first line*/
	write_lcd(0, 2, 0xc0);	
	
	write_lcd(0, 1, 0x3f);/*set display on*/
	write_lcd(0, 2, 0x3f);
	
	for(j= 0; j<=7; j++){/*左クリア*/
		for(i=0; i<64; i++){
			point_lcd(i, j);	
			write_lcd(1, 1, 0x00);
		}
	}
	
	for(j= 0; j<=7; j++){/*右クリア*/
		for(i=64; i<128; i++){
			point_lcd(i, j);
			write_lcd(1, 2, 0x00);
		}
	}
}

/*描画座標指定関数*/
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


/*縦8ドットの描画関数*/
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

/*文字表示座標指定関数*/
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

/*文字表示関数*/
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

/*文字列表示関数*/
void design_string(int x, int page, unsigned char *data_cnt, int data_len)
{	
	int cs;
	int i,j;	
	
	unsigned char data[80];
	unsigned char str[80];
	
	int word_len = data_len * 8;
	
	int left,right;
	int range = x + word_len -1;
	
	strcpy(data,data_cnt);/*文字のコピー*/
	
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

/*数字→文字列変換＋表示*/
void design_number(int x, int page, int data_num)
{
	int i, data_len;	
	/*3桁*/
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

/*画像表示関数*/
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
 
/*LED下部*/
void LCD_light()
{
	long int i;

    P9.DDR = 0x01;                 /* P9の0 を出力に設定 */

    while (1) {
        for (i = 0; i < WAIT; i++);
        P9.DR.BYTE = 0x00;           /* LED 消灯（バイト単位代入） */

        for (i = 0; i < WAIT; i++);
        P9.DR.BIT.B0 = 1;            /* LED 点灯（ビット単位代入） */
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
	
	strcpy(data,data_cnt);/*文字のコピー*/
	
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

/*ディスプレイ全画面表示*/
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

