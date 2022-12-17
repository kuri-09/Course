//Pump.c

#include "iodefine.h"

void Pump_drain_water(){
	
	//‹‹…
	DA.DADR1 = 0xff;
	//DA.DACR.BIT.DAOE1 = 1;

}

void Pump_stop_drain(){
	
	//‹‹…’†~
	DA.DADR1 = 0x00;
	//DA.DACR.BIT.DAOE1 = 1;

}