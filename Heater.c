//Heater.c
#include "iodefine.h"

#include <stdio.h>


/*PID????*/
void Heater_control(unsigned char power){

	DA.DADR0 = power;//‘€ì—Ê
	
}



