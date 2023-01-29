/*SupplyWaterFunction*/
#include "KettleSystem.h"
#include "macro.h"
#include "struct.h"

void SupplyWaterFunction_supply_water(SYSTEM_CLASS *SYSTEM, INTERRUPT_CLASS *INTERRUPT, MANAGER_CLASS *MANAGER){

    //lock or unlock gate
    if(MANAGER->FLAG.SUPPLY.PUSH_LOCK_BUTTON == HIGH && MANAGER->FLAG.SUPPLY.SOUND_BUZZER == HIGH){

        if(SYSTEM->LOCK.GATE_STATE == CLOSE){

            SYSTEM->LOCK.GATE_STATE = OPEN;

        }else if(SYSTEM->LOCK.GATE_STATE == OPEN){

            SYSTEM->LOCK.GATE_STATE = CLOSE;
        }

        //ring buzzer
        Buzzer_ring_buzzer(1);

    }

    if(SYSTEM->LOCK.GATE_STATE == OPEN){
        LockLamp_turn_off_lamp();
    }else if(SYSTEM->LOCK.GATE_STATE == CLOSE){
        LockLamp_turn_on_lamp();
    }

    //supply water
    if(MANAGER->FLAG.SUPPLY.PUSH_SUPPLY_BUTTON == HIGH && SYSTEM->LOCK.GATE_STATE == OPEN && INTERRUPT->INPUT.WATER_LEVEL != EMPTY){

        //supply water
        Pump_drain_water();

    }else{

        //stop supply water
        Pump_stop_drain();

    }

}