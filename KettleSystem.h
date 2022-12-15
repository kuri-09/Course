//KettleSystem.h
/*
#include "BoilingFunction.h"
#include "KeepWarmFunction.h"
#include "SupplyWaterFunction.h"
#include "KitchenTimerFunction.h"
*/

struct KettleSystem{
	int boiling_result;
	int keep_warm_result;
	int supply_wate_state;
	int kitchen_timer_state;
};


typedef enum{
	
	show_timer,
	button,
	//water_level,
	cover,
	
}flag;


typedef enum{
	
	unlock,
	boil,
	supply,
	timer,
	keep,
	
}btn;

typedef enum{
	
	off,
	boiling,
	pid,

}heat;