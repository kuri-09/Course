/*Manager.c*/

#include "KettleSystem.h"
#include "iodefine.h"

#define MINUTE 6000
#define SECOND 100

/*�O���[�o���ϐ�*/
heat heat_state;
int time_out;

/*extern*/
extern int remaining_time = 0;
extern unsigned long int temp;

void Manager_interrupt(unsigned char button_state, int water_level, int cover_state){
	
	btn btn_type;
	int i = 0;
	static int boillamp_state;
	static int keeplamp_state;
	static int locklamp_state;
	static int cnt_interrupt;
	static int buzzer_type;
	unsigned char pb_state = 0x00;
	
	
	if(buzzer_type != -1){
		Buzzer_turn_off();
		Buzzer_turn_off_enable();
		buzzer_type = -1;
	}
	
	if(temp > 100){
		DA.DADR0 = 0x00;
	}
	
	/*�^�C�}���荞�݁F�^�C�}*/
	
	if(time_out != 0){
		if(cnt_interrupt != 0){
			//�u�U�[�Fon
			Buzzer_turn_on_enable();
			Buzzer_turn_on();
			buzzer_type = show_timer;
		}
		time_out = 0;
	}


	/*�^�C�}���荞�݁F�{�^��*/
	
	//btn_type = unlock;
	if((button_state & 0x01) == 0x01 && locklamp_state == 0){
		
		//�����v:on
		Lock_Lamp_turn_on_lamp();
		locklamp_state = 1;
		
		//�u�U�[�Fon
		Buzzer_turn_on_enable();
		Buzzer_turn_on();
		buzzer_type = unlock;
		
		//I/O�|�[�gB
		pb_state += 0x40; 
	
	}else if((button_state & 0x01) == 0x01 && locklamp_state == 1){
		
		//I/O�|�[�gB
		pb_state += 0x40;
		
	}else{
		
		//�����v:off
		Lock_Lamp_turn_off_lamp();
		locklamp_state = 0;
 
	}
	
	
	//btn_type = boil;
	if((button_state & 0x02) == 0x02 && boillamp_state == 0){
		
		//�����v:on
		Boil_Lamp_turn_on_lamp();
		boillamp_state = 1;
		
		//�u�U�[�Fon
		Buzzer_turn_on_enable();
		Buzzer_turn_on();
		buzzer_type = boil;
		
		//�q�[�^�@���@boil
		heat_state = boiling;
		
		//I/O�|�[�gB
		pb_state += 0x10; 
	
	}else if((button_state & 0x02) == 0x02 && boillamp_state == 1){
		
		//I/O�|�[�gB
		pb_state += 0x10; 
		
	}else{
		
		//�����v:off
		Boil_Lamp_turn_off_lamp();
		boillamp_state = 0;

	}		
		
		
	//btn_type = supply_water;
	if((button_state & 0x04) == 0x04){
		
		Pump_drain_water();
		
	}else{
		
		Pump_stop_drain();
		
	}
		
	//btn_type = timer;
	if((button_state & 0x08) == 0x08){
		if(remaining_time != 60)
		    remaining_time += 1;
		   
	}
	
	//btn_type = set_keep_mode;
	if((button_state & 0x10) == 0x10 && keeplamp_state == 0){
		
		//�����v:on
		Keep_Lamp_turn_on_lamp();
		keeplamp_state = 1;
		
		//�u�U�[�Fon
		Buzzer_turn_on_enable();
		Buzzer_turn_on();
		buzzer_type = keep;
		
		//I/O�|�[�gB
		pb_state += 0x20;
		
		/*�����̒��~*/
		DA.DADR0 = 0x00;//�o�͒l�̐ݒ�
		HeaterPower_turn_off();
		heat_state = off;
		
	
	}else if((button_state & 0x10) == 0x10 && keeplamp_state == 1){
		
		//I/O�|�[�gB
		pb_state += 0x20; 
		
	}else{
		
		//�����v:off
		Keep_Lamp_turn_off_lamp();
		keeplamp_state = 0;
	}
	
	
	/*�^�C�}���荞�݁F����(1000)*/
	
	pb_state = (pb_state | (water_level & 0x0f));
	WaterLevelMeter_show_water_level(pb_state);
	
	
	/*�^�C�}���荞�݁F�ӂ�(100)*/
	
	if(cover_state == 1){//�܂��Ă���Ƃ�
	
		Boil_Lamp_turn_on_lamp();
		Keep_Lamp_turn_on_lamp();
		Lock_Lamp_turn_on_lamp();
	}
	
	/*�Ăяo���񐔂̏�����*/
	if(cnt_interrupt < 10){
		cnt_interrupt++;
	}else{
		cnt_interrupt = 1;	
	}
}