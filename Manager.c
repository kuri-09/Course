/*Manager.c*/

#include "KettleSystem.h"
#include "extern.h"
#include "struct.h"

#include "iodefine.h"



void Manager_interrupt(SYSTEM_CLASS *SYSTEM, INTERRUPT_CLASS *INTERRUPT, MANAGER_CLASS *MANAGER){

	int i = 0;
	static int before_cover_state;
	
	/* 割込みの情報の処理 */

	//push lock button
	if((INTERRUPT->INPUT.BUTTON_STATE & 0x01) == UNLOCK && MANAGER->FLAG.SUPPLY.PUSH_LOCK_BUTTON == LOW){

		MANAGER->FLAG.SUPPLY.PUSH_LOCK_BUTTON = HIGH;
		MANAGER->FLAG.SUPPLY.SOUND_BUZZER = HIGH;
	
	}else if((INTERRUPT->INPUT.BUTTON_STATE & 0x01) == UNLOCK && MANAGER->FLAG.SUPPLY.PUSH_LOCK_BUTTON == HIGH){

		MANAGER->FLAG.SUPPLY.SOUND_BUZZER = LOW;

	}else{

		MANAGER->FLAG.SUPPLY.PUSH_LOCK_BUTTON = LOW;
		MANAGER->FLAG.SUPPLY.SOUND_BUZZER = LOW;
		
	}
	
	//push boil button
	if((INTERRUPT->INPUT.BUTTON_STATE & 0x02) == BOIL && MANAGER->FLAG.BOIL.PUSH_BOIL_BUTTON == LOW 
	&& (INTERRUPT->INPUT.WATER_LEVEL != EMPTY && INTERRUPT->INPUT.WATER_LEVEL != FULL)
	&& (MANAGER->HEATER != BOIL || MANAGER->HEATER != DESCALING)
	&& INTERRUPT->INPUT.COVER_STATE == COVER_CLOSE){
		
		MANAGER->FLAG.BOIL.PUSH_BOIL_BUTTON = HIGH;
		MANAGER->FLAG.BOIL.SOUND_BUZZER = HIGH;
	
	}else if((INTERRUPT->INPUT.BUTTON_STATE & 0x02) == BOIL && MANAGER->FLAG.BOIL.PUSH_BOIL_BUTTON == HIGH){

		MANAGER->FLAG.BOIL.SOUND_BUZZER = LOW;
		
	}else{
		
		MANAGER->FLAG.BOIL.PUSH_BOIL_BUTTON = LOW;
		MANAGER->FLAG.BOIL.SOUND_BUZZER = LOW;

	}		
	
	//push supply_water button;
	if((INTERRUPT->INPUT.BUTTON_STATE & 0x04) == SUPPLY){

		MANAGER->FLAG.SUPPLY.PUSH_SUPPLY_BUTTON = HIGH;

	}else{

		MANAGER->FLAG.SUPPLY.PUSH_SUPPLY_BUTTON = LOW;

	}
		
	//push timer button
	if((INTERRUPT->INPUT.BUTTON_STATE & 0x08) == TIMER && MANAGER->FLAG.KITCHEN.PUSH_TIMER_BUTTON == LOW){

		if(SYSTEM->TIMER.REMAINING_TIME != 60){
		    
			SYSTEM->TIMER.REMAINING_TIME += 1;
			MANAGER->FLAG.KITCHEN.PUSH_TIMER_BUTTON = HIGH;
			MANAGER->FLAG.KITCHEN.SOUND_BUZZER = HIGH;

		} 

	}else if((INTERRUPT->INPUT.BUTTON_STATE & 0x08) == TIMER && MANAGER->FLAG.KITCHEN.PUSH_TIMER_BUTTON == HIGH){

		MANAGER->FLAG.KITCHEN.SOUND_BUZZER = LOW;

	}else{

		MANAGER->FLAG.KITCHEN.PUSH_TIMER_BUTTON = LOW;
		MANAGER->FLAG.KITCHEN.SOUND_BUZZER = LOW;

	}
	
	//push set_keep_mode button
	if((INTERRUPT->INPUT.BUTTON_STATE & 0x10) == KEEP && MANAGER->FLAG.KEEP.PUSH_KEEP_BUTTON == LOW){

		MANAGER->FLAG.KEEP.PUSH_KEEP_BUTTON = HIGH;
		MANAGER->FLAG.KEEP.SOUND_BUZZER = HIGH;
	
	}else if((INTERRUPT->INPUT.BUTTON_STATE & 0x10) == KEEP && MANAGER->FLAG.KEEP.PUSH_KEEP_BUTTON == HIGH){

		MANAGER->FLAG.KEEP.SOUND_BUZZER = LOW;
		
	}else{

		MANAGER->FLAG.KEEP.PUSH_KEEP_BUTTON = LOW;
		MANAGER->FLAG.KEEP.SOUND_BUZZER = LOW;

	}
	
	/* display water level (1000) */
	WaterLevelMeter_show_water_level(INTERRUPT->INPUT.WATER_LEVEL);

	/* display water temp (100) */
	design_display_temp(INTERRUPT->INPUT.DISPLAY_WATER_TEMP);

	/* display keep mode */
	design_display_mode(SYSTEM->KEEP.MODE);

	/* close cover (100) */
	if(INTERRUPT->INPUT.COVER_STATE == COVER_CLOSE && before_cover_state == COVER_OPEN){

		MANAGER->HEATER = BOILING;

	}
	
	/* open cover or controllable water level*/
	if(INTERRUPT->INPUT.COVER_STATE == COVER_OPEN || INTERRUPT->INPUT.WATER_LEVEL == EMPTY || INTERRUPT->INPUT.WATER_LEVEL == FULL){
	
		MANAGER->HEATER = OFF;
		Heater_control(0x00);

		MANAGER->FLAG.BOIL.START_DESCALING = LOW;

	}

	before_cover_state = INTERRUPT->INPUT.COVER_STATE;

}