/*KitchenTimerFunction*/
#include "KettleSystem.h"
#include "macro.h"
#include "struct.h"

void KitchenTimerFunction_timer(SYSTEM_CLASS *SYSTEM, INTERRUPT_CLASS *INTERRUPT, MANAGER_CLASS *MANAGER){

	//
	if(MANAGER->FLAG.KITCHEN.PUSH_TIMER_BUTTON == HIGH && MANAGER->FLAG.KITCHEN.SOUND_BUZZER == HIGH){

		MANAGER->FLAG.KITCHEN.START_COUNT_DOWN = HIGH;

	}
	
	if(MANAGER->FLAG.KITCHEN.SOUND_BUZZER == HIGH){

		//ring buzzer
		Buzzer_ring_buzzer(1);

	}
	
    //Kitchen Timer is time out
	if(INTERRUPT->FLAG.KITCHEN.TIME_OUT == HIGH){
		
		MANAGER->FLAG.KITCHEN.START_COUNT_DOWN = LOW;
		INTERRUPT->FLAG.KITCHEN.TIME_OUT = LOW;
		
		//ring buzzer (3 times)
		Buzzer_ring_buzzer(3);
	}

}