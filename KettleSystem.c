/* KettleSystem.c */

/*0.5E½ð«ï¿½E½E½intE½ÉÏï¿½E½E½E½lE½ÌÜï¿½
E½E½E½bE½NE½{E½^E½E½E½E½E½E½E½E½E½Èï¿½E½E½AE½dE½E½E½E½E½E½E½E½E½100E½E½E½E½E½E½XE½^E½[E½g*/

/*¦¢gpÌ|[gÍüÍÉ·éÌª}i[*/
/*0ª«A1ªÇÝ*/

/*ÎQÆ*/
#include "iodefine.h"

#include "KettleSystem.h"
#include "struct.h"

/*âÎQÆ*/
#include <stdio.h>
#include <string.h>

/*vg^Cvé¾*/
void init();
void init_sci1(unsigned char b_rate);
void charput(char c);

/*\¢ÌÌé¾*/
SYSTEM_CLASS SYSTEM;
INTERRUPT_CLASS INTERRUPT;
MANAGER_CLASS MANAGER;
ERROR_CLASS ERROR;

int main(void)
{
	int i = 0;
	double ad = 0;
	const unsigned char data[] = "Keita_Igarashi";
	int data_len = strlen(data);
	/*---------*/
	/*---------*/
	
	//init
	init();
	init_sci1(80);//portF9600 [baud]
	
	while(1){

		//^C}èÝÅæ¾µ½f[^ðgÁ½
		Manager_interrupt(&SYSTEM, &INTERRUPT, &MANAGER);

		//check error
		Error_check_error(&SYSTEM, &INTERRUPT, &MANAGER, &ERROR);
		
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
	
	/* ADÏ·Ì×ÌúÝè */
	AD.ADCSR.BYTE = 0x40;
	
	/* DAÏ·Ì×ÌúÝè */
	DA.DADR0 = 0x00;
	DA.DACR.BIT.DAOE0 = 1;
	DA.DADR1 = 0x00;
	DA.DACR.BIT.DAOE1 = 1;
	
	/* q[^d¹ðÁ·é */
	HeaterPower_turn_off();

	/* uU[Cl[uðÁ */
	Buzzer_turn_off_enable();
	
	//|[gÌÝè
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
	SCI1.SCR.BYTE = 0; // E½E½E½E½E½lE½E½ 0
    SCI1.SMR.BYTE = 0; // E½E½E½E½E½lE½E½ 0
	SCI1.BRR = b_rate; // E½rE½bE½gE½E½E½[E½g
	for (i = 0; i < 4000; i++); // E½Òï¿½
	SCI1.SCR.BYTE = 0x70; // E½E½ME½E½E½èï¿½Ýï¿½E½ÂCE½E½E½E½ME½E½E½E½
	SCI1.SSR.BYTE; // E½_E½~E½[E½E½E½[E½h
	SCI1.SSR.BYTE = 0x80; // E½GE½E½E½[E½tE½E½E½OE½NE½E½E½A
}

void charput(char c)
{
	while (!SCI1.SSR.BIT.TDRE); // E½E½E½ME½E½Òï¿½
	SCI1.TDR = c;
	SCI1.SSR.BIT.TDRE = 0; // TDREE½NE½E½E½A
}
