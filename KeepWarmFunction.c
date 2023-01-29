/*KeepWarmFunction*/
#include "KettleSystem.h"
#include "macro.h"
#include "struct.h"

double KeepWarmFunction_calculate_power(double before_temp, double pid_temp, unsigned int target_temp,unsigned char is_first);

void KeepWarmFunction_keep_warm(SYSTEM_CLASS *SYSTEM, INTERRUPT_CLASS *INTERRUPT, MANAGER_CLASS *MANAGER){

    static unsigned char power;
    unsigned int target_temp[3] = {98, 90, 60};

    if(MANAGER->FLAG.KEEP.PUSH_KEEP_BUTTON == HIGH && MANAGER->FLAG.KEEP.SOUND_BUZZER == HIGH){

        //change keep mode
        if(SYSTEM->KEEP.MODE <= 1){
			SYSTEM->KEEP.MODE += 1; 
		}else{
			SYSTEM->KEEP.MODE = 0; 
		}

        //re-boiling
        if(MANAGER->HEATER != BOIL || MANAGER->HEATER != DESCALING){

            MANAGER->HEATER = BOILING;

        }

        //ring buzzer
        Buzzer_ring_buzzer(1);

    }

    //natural cooling
    if(MANAGER->HEATER == COOL){

        power = 0x00;

        //set lamp state
        BoilLamp_turn_off_lamp();
        KeepWarmLamp_turn_off_lamp();

        if(INTERRUPT->INPUT.WATER_TEMP < target_temp[SYSTEM->KEEP.MODE]){

            MANAGER->HEATER = PID;
            MANAGER->FLAG.KEEP.START_KEEP_WARM = HIGH;

        }

        //Output to heater
        Heater_control(power);

    }

    //PID control
    if(MANAGER->HEATER == PID){

        //set lamp state
        BoilLamp_turn_off_lamp();
        KeepWarmLamp_turn_on_lamp();

        if(INTERRUPT->FLAG.KEEP.DECIDE_PID_VALUE == HIGH){
            
            if(MANAGER->FLAG.KEEP.START_KEEP_WARM == HIGH){
                
                power = ((unsigned char)KeepWarmFunction_calculate_power(INTERRUPT->INPUT.BEFORE_TEMP, INTERRUPT->INPUT.WATER_TEMP, target_temp[SYSTEM->KEEP.MODE], MANAGER->FLAG.KEEP.START_KEEP_WARM));	
                MANAGER->FLAG.KEEP.START_KEEP_WARM = LOW;
            
            }else if(MANAGER->FLAG.KEEP.START_KEEP_WARM == LOW){
                
                power = ((unsigned char)KeepWarmFunction_calculate_power(INTERRUPT->INPUT.BEFORE_TEMP, INTERRUPT->INPUT.WATER_TEMP, target_temp[SYSTEM->KEEP.MODE], MANAGER->FLAG.KEEP.START_KEEP_WARM));

            }
            
            //Output to heater
            Heater_control(power);
            INTERRUPT->FLAG.KEEP.DECIDE_PID_VALUE = LOW;

        }
		
	}

    //set lamp and heater power
    if(MANAGER->HEATER == COOL || MANAGER->HEATER == PID){
        
        //set lamp state
        KeepWarmLamp_turn_on_lamp();
    
    }else{

        KeepWarmLamp_turn_off_lamp();
        
    }

}

double KeepWarmFunction_calculate_power(double before_temp, double pid_temp, unsigned int target_temp, unsigned char is_first){
	
	static double before_e;
    static double area;
	double e;
	double p;
	double i;
	double d;
	double u;

    if(is_first == HIGH){
        area = 0.0;
    }

    //Determining parameters
    e = target_temp - pid_temp;
    p = e;
    i = area + ((e + before_e) * (T / 2));
    d = (pid_temp - before_temp) / T;
	
    //Save value
	before_e = e;
	area = i;
	
	//Determination of manipulated variable of PID control
	u = KP * (p + (i / TI) + (d * TD));
	
	if(u <= 0.0)
	    u = 0.0;
	if(u >= 255.0)
	    u = 255.0;

    return u;
}