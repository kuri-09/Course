//KettleSystem.h
/*
#include "BoilingFunction.h"
#include "KeepWarmFunction.h"
#include "SupplyWaterFunction.h"
#include "KitchenTimerFunction.h"
*/
/*
#include "function.h"
#include "controll_object.h"
#include "data.h"
*/
struct KettleSystem{
	int boiling_result;
	int keep_warm_result;
	int supply_water_state;
	int kitchen_timer_state;
};

typedef enum{
	
	SHOW_TIMER,
	BUTTON,
	//water_level,
	COVER,
	
}FLAG_TYPE;


typedef enum{
	
	UNLOCK = 1,
	BOIL = 2,
	SUPPLY = 4,
	TIMER = 8,
	KEEP = 16,
	
}BUTTON_TYPE;

typedef enum{
	
	EMPTY = 0,
	FULL = 31,
	
}WATER_LEVEL;

typedef enum{
	
	OFF,
	BOILING,
	DESCALING,
	COOL,
	PID,

}HEATER_TYPE;

typedef enum{
	
	CLOSE,
	OPEN,

}GATE_STATE;

typedef enum{
	
	LOW,
	HIGH,

}FLAG_STATE;

typedef enum{
	
	TRUE,
	FALSE,

}AUTHENTICITY;

typedef enum{
	
	COVER_OPEN,
	COVER_CLOSE,

}COVER_STATE;