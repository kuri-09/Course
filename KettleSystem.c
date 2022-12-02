/* KettleSystem.c */
/*※未使用のポートは入力にするのがマナー*/
/*Eがoffのときは待ち状態であり、onにした瞬間に実行される*/
/*0が書き、1が読み*/

#include "iodefine.h"

#include "KettleSystem.h"

#include <stdio.h>
#include <string.h>

#define SECOND 1000

//保温設定の変更と給湯口の変更（構造体の書き換えが上手くいっていない）
//ケトルシステムから機能に飛んで、更にその内部の関数に飛んだときに、書き換えられていない

int main(void)
{
	int i = 0;
	const unsigned char data[] = "Keita_Igarashi";
	int data_len = strlen(data);
	
	//LCDの初期化
	reset_lcd();
	
	/*文字表示*/
	design_char(60, 0, 'A');
	
	/*文字列表示*/
	design_string(60, 3, data, data_len);
	
	/*数字→文字列変換＋表示*/
	design_number(0, 5, 999);
	wait_ms(SECOND);
	
	/*画像表示関数*/
	design_image();
	wait_ms(SECOND/2);
	
	reset_lcd();
	
	//LCDに出力
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






