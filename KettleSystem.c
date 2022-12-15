/* KettleSystem.c */
/*※未使用のポートは入力にするのがマナー*/
/*Eがoffのときは待ち状態であり、onにした瞬間に実行される*/
/*0が書き、1が読み*/

#include "iodefine.h"

#include "KettleSystem.h"

#include <stdio.h>
#include <string.h>

#define SECOND 1000

//グローバル変数
int temp = 0;
int ad_temp = 0;
//int remaining_time = 0;
unsigned char water_level = 0x00;
unsigned char button_state = 0x00;
int cover_state = 0;

//プロトタイプ宣言
void init();

//保温設定の変更と給湯口の変更（構造体の書き換えが上手くいっていない）
//ケトルシステムから機能に飛んで、更にその内部の関数に飛んだときに、書き換えられていない

int main(void)
{
	int i = 0;
	const unsigned char data[] = "Keita_Igarashi";
	int data_len = strlen(data);
	//int test_temp;
	
	//初期化
	init();
	
	//LCDの初期化
	reset_lcd();
	
	/*数字→文字列変換＋表示*/
	//design_number(0, 5, 999);

	//LCDに保温モードの出力
	//design_display_mode(98);
	
	
	while(1){
		
		temp = (125 * ad_temp) /1024;
		design_display_temp(temp);
		
		//タイマ割り込みでサンプリングした値を処理する
		Manager_interrupt(button_state, water_level, cover_state);
		wait_ms(100);
		
		design_number(0, 5, temp);
			
	}
	
    return 0;
}

void init(){
	
	//AD変換
	AD.ADCSR.BIT.SCAN = 0;//動作モードの選択(単一)
	AD.ADCSR.BIT.ADIE = 1;//割り込みの許可
	AD.ADCSR.BIT.CH = 0x00;//チャンネルの選択
	
	//DA変換
	//ヒータ
	DA.DADR0 = 0x00;//出力初期値の設定
	DA.DACR.BIT.DAOE0 = 1;//出力の許可
	
	//ポンプ
	DA.DADR1 = 0x00;
	DA.DACR.BIT.DAOE1 = 1;
	
	//ブザー・ヒータ電源
	P6.DDR = 0xff;//高温エラーなくなる
	HeaterPower_turn_off();
}