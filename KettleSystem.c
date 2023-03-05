/* KettleSystem.c */


/*Eがoffのときは待ち状態であり、onにした瞬間に実行される*/
/*※未使用のポートは入力にするのがマナー*/
/*0が書き、1が読み*/

/*相対参照*/
#include "iodefine.h"

#include "KettleSystem.h"
#include "struct.h"

/*絶対参照*/
#include <stdio.h>
#include <string.h>

/*プロトタイプ宣言*/
void init();
void init_sci1(unsigned char b_rate);
void charput(char c);

/*構造体の宣言*/
SYSTEM_CLASS SYSTEM;
INTERRUPT_CLASS INTERRUPT;
MANAGER_CLASS MANAGER;
ERROR_CLASS ERROR;


int main(void)
{
	
	//init
	init();
	init_sci1(80);//port：9600 [baud]
	
	while(1){

		//タイマ割り込みで取得したデータを使った処理
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
	
	/* AD変換の為の初期設定 */
	AD.ADCSR.BYTE = 0x40;
	
	/* DA変換の為の初期設定 */
	DA.DADR0 = 0x00;
	DA.DACR.BIT.DAOE0 = 1;
	DA.DADR1 = 0x00;
	DA.DACR.BIT.DAOE1 = 1;
	
	/* ヒータ電源を消灯する */
	HeaterPower_turn_off();

	/* ブザーイネーブルを消灯 */
	Buzzer_turn_off_enable();
	
	//ポートの設定
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
	SCI1.SCR.BYTE = 0; // ・ｽ・ｽ・ｽ・ｽ・ｽl・ｽ・ｽ 0
    SCI1.SMR.BYTE = 0; // ・ｽ・ｽ・ｽ・ｽ・ｽl・ｽ・ｽ 0
	SCI1.BRR = b_rate; // ・ｽr・ｽb・ｽg・ｽ・ｽ・ｽ[・ｽg
	for (i = 0; i < 4000; i++); // ・ｽﾒゑｿｽ
	SCI1.SCR.BYTE = 0x70; // ・ｽ・ｽM・ｽ・ｽ・ｽ闕橸ｿｽﾝ具ｿｽ・ｽﾂ，・ｽ・ｽ・ｽ・ｽM・ｽ・ｽ・ｽ・ｽ
	SCI1.SSR.BYTE; // ・ｽ_・ｽ~・ｽ[・ｽ・ｽ・ｽ[・ｽh
	SCI1.SSR.BYTE = 0x80; // ・ｽG・ｽ・ｽ・ｽ[・ｽt・ｽ・ｽ・ｽO・ｽN・ｽ・ｽ・ｽA
}

void charput(char c)
{
	while (!SCI1.SSR.BIT.TDRE); // ・ｽ・ｽ・ｽM・ｽ・ｽﾒゑｿｽ
	SCI1.TDR = c;
	SCI1.SSR.BIT.TDRE = 0; // TDRE・ｽN・ｽ・ｽ・ｽA
}

/*
int i = 0;
double ad = 0;
const unsigned char data[] = "Keita_Igarashi";
int data_len = strlen(data);
*/