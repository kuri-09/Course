/* Error.c */

/*KeepWarmFunction*/
#include "KettleSystem.h"
#include "macro.h"
#include "struct.h"

void Error_check_error(SYSTEM_CLASS *SYSTEM, INTERRUPT_CLASS *INTERRUPT, MANAGER_CLASS *MANAGER, ERROR_CLASS *ERROR){

    unsigned int target_temp[3] = {98, 90, 60};

    /*high temperature error*/
    if(MANAGER->HEATER != OFF){

        if(INTERRUPT->INPUT.DISPLAY_WATER_TEMP >= 110){

            ERROR->FLAG.HAPPEN_HIGH_TEMP = HIGH;
            
            //heater and heater power off
            MANAGER->HEATER = OFF;
            HeaterPower_turn_off();

            //ring for 30 seconds
            Buzzer_turn_on_enable();
            while(INTERRUPT->FLAG.ERROR.PASSED_THIRTY_SECONDS == LOW){
               Buzzer_turn_on();
            }
            Buzzer_turn_off();
            Buzzer_turn_off_enable();

            //reset
            INTERRUPT->FLAG.ERROR.PASSED_THIRTY_SECONDS = LOW;

        }

    }


    /*Unable to heat error*/
    if(MANAGER->HEATER != OFF){

        ERROR->FLAG.START_CHECK_ERROR = HIGH;

        if(INTERRUPT->FLAG.ERROR.PASSED_ONE_MINUTE == HIGH){

            INTERRUPT->FLAG.ERROR.PASSED_ONE_MINUTE = LOW;

            if(MANAGER->HEATER == BOILING || MANAGER->HEATER == DESCALING){

                if(INTERRUPT->INPUT.BEFORE_TEMP > INTERRUPT->INPUT.WATER_TEMP && 100 >= (INTERRUPT->INPUT.WATER_TEMP + 5.0)){
                
                    ERROR->FLAG.HAPPEN_UNABLE_TO_HEAT = HIGH;
                    
                    //heater and heater power off
                    MANAGER->HEATER = OFF;
                    HeaterPower_turn_off();

                    //ring for 30 seconds
                    Buzzer_turn_on_enable();
                    while(INTERRUPT->FLAG.ERROR.PASSED_THIRTY_SECONDS == LOW){
                        Buzzer_turn_on();
                    }
                    Buzzer_turn_off();
                    Buzzer_turn_off_enable();

                    //reset
                    INTERRUPT->FLAG.ERROR.PASSED_THIRTY_SECONDS = LOW;
                }

            }else if(MANAGER->HEATER == COOL || MANAGER->HEATER == PID){

                if(INTERRUPT->INPUT.BEFORE_TEMP > INTERRUPT->INPUT.WATER_TEMP && target_temp[SYSTEM->KEEP.MODE] >= (INTERRUPT->INPUT.WATER_TEMP + 5.0)){
                    
                    ERROR->FLAG.HAPPEN_UNABLE_TO_HEAT = HIGH;
                    
                    //heater and heater power off
                    MANAGER->HEATER = OFF;
                    HeaterPower_turn_off();
                    
                    //ring for 30 seconds
                    Buzzer_turn_on_enable();
                    while(INTERRUPT->FLAG.ERROR.PASSED_THIRTY_SECONDS == LOW){
                        Buzzer_turn_on();
                    }
                    Buzzer_turn_off();
                    Buzzer_turn_off_enable();

                    //reset
                    INTERRUPT->FLAG.ERROR.PASSED_THIRTY_SECONDS = LOW;
                }
                
            }

        }

    }else{
        ERROR->FLAG.START_CHECK_ERROR = LOW;
    }

}
