/*BoilFunction*/
#include "KettleSystem.h"
#include "extern.h"
#include "macro.h"
#include "struct.h"

void BoilFunction_boil(SYSTEM_CLASS *SYSTEM, INTERRUPT_CLASS *INTERRUPT, MANAGER_CLASS *MANAGER){

    unsigned char power = 0x00;

    if(MANAGER->FLAG.BOIL.PUSH_BOIL_BUTTON == HIGH || MANAGER->FLAG.KEEP.PUSH_KEEP_BUTTON == HIGH){

        if(MANAGER->HEATER != BOILING && MANAGER->FLAG.BOIL.SOUND_BUZZER == HIGH){

            MANAGER->HEATER = BOILING;

            //ring buzzer
            Buzzer_ring_buzzer(1);

        }  

    }
    
    //set lamp and heater power
    if(MANAGER->HEATER == BOILING || MANAGER->HEATER == DESCALING){
        
        //set lamp state
        BoilLamp_turn_on_lamp();
        
        //set heater power state
        HeaterPower_turn_on();
    
    }else{

        BoilLamp_turn_off_lamp();
        
    }
    
    //boiling water
    if(MANAGER->HEATER == BOILING){
        
        if(INTERRUPT->INPUT.DISPLAY_WATER_TEMP < 100){
            
            power = 0xff;

        }else if(INTERRUPT->INPUT.DISPLAY_WATER_TEMP >= 100){
            
            power = 0xff;
            MANAGER->HEATER = DESCALING;
            MANAGER->FLAG.BOIL.START_DESCALING = HIGH;

        }

        //Output to heater
        Heater_control(power);

    }

    //descaled after 3 minutes
    if(INTERRUPT->FLAG.BOIL.PASSED_THREE_MINUTES == HIGH){

        MANAGER->FLAG.BOIL.START_DESCALING = LOW;
        INTERRUPT->FLAG.BOIL.PASSED_THREE_MINUTES = LOW;

    }

    //descaling water
    if(MANAGER->HEATER == DESCALING){

        if(MANAGER->FLAG.BOIL.START_DESCALING == HIGH){

            power = 0xff;

        //3 minute after
        }else if(MANAGER->FLAG.BOIL.START_DESCALING == LOW){

            power = 0x00;
            MANAGER->HEATER = COOL;
            
            //ring buzzer (3 times)
            Buzzer_ring_buzzer(3);

        }

        //Output to heater
        Heater_control(power);

    }

}