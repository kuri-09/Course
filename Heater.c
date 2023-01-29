//Heater.c
#include "iodefine.h"
#include "KettleSystem.h"
#include "extern.h"
#include "macro.h"

#include <stdio.h>
#include <math.h>


/*PID????*/
void Heater_control(unsigned char power){

	DA.DADR0 = power;//‘€ì—Ê
	
}



