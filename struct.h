/*ç\ë¢ëÃ*/

typedef struct{
	
		/*
		struct{
			unsigned char ;
		}BOIL;
		*/
		struct{
			unsigned char MODE;
		}KEEP;
		
		struct{
			unsigned char GATE_STATE;
		}LOCK;
		
		struct{
			unsigned char REMAINING_TIME;
		}TIMER;
		
	
}SYSTEM_CLASS;

typedef struct{
		
		struct{
			
			double BEFORE_TEMP;
			unsigned char COVER_STATE;
			unsigned char BUTTON_STATE;
			unsigned char WATER_LEVEL;
			double WATER_TEMP;
			int DISPLAY_WATER_TEMP;
		
		}INPUT;

		struct{
			
			struct{
				unsigned char PASSED_THREE_MINUTES;
			}BOIL;
			
			struct{
				unsigned char DECIDE_PID_VALUE;
			}KEEP;
			
			/*struct{
		    }SUPPLY;*/
			
			struct{
				unsigned char TIME_OUT;
			}KITCHEN;

			struct{
				unsigned char PASSED_THIRTY_SECONDS;
				unsigned char PASSED_ONE_MINUTE;
			}ERROR;
		
		}FLAG;
	
}INTERRUPT_CLASS;

typedef struct{
	
	unsigned char HEATER;

	struct{

		struct{

			unsigned char START_DESCALING;
			unsigned char PUSH_BOIL_BUTTON;
			unsigned char SOUND_BUZZER;

		}BOIL;

		struct{

			unsigned char START_KEEP_WARM;
			unsigned char PUSH_KEEP_BUTTON;
			unsigned char SOUND_BUZZER;

		}KEEP;

		struct{

			unsigned char PUSH_SUPPLY_BUTTON;
			unsigned char PUSH_LOCK_BUTTON;
			unsigned char SOUND_BUZZER;

		}SUPPLY;

		struct{

			unsigned char START_COUNT_DOWN;
			unsigned char PUSH_TIMER_BUTTON;
			unsigned char SOUND_BUZZER;

		}KITCHEN;
			
	}FLAG;

}MANAGER_CLASS;

typedef struct{
	
	struct{

		unsigned char START_CHECK_ERROR;
		unsigned char HAPPEN_HIGH_TEMP;
		unsigned char HAPPEN_UNABLE_TO_HEAT;
				
	}FLAG;

}ERROR_CLASS;