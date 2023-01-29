////ModeDisplay.c

#include "iodefine.h"
#include "ModeDisplay.h"

#include "Display.h"

/*ƒ‚[ƒh‚Ì•\¦*/
void design_display_mode(int target_temp)
{
	
	int cs;
	int x = 0;
	int page = 0;
	
	int mode = target_temp;
	
	for(page=5; page<8; page++){
		for(x=64; x<128; x++){
			cs = point_image(x, page);
			write_lcd(1, cs, display_fixed[page-5][x-64]);
		}
	}

	for(page=5; page<8; page++){
		for(x=0; x<64; x++){
			cs = point_image(x, page);
		    write_lcd(1, cs, display_mode[mode][page-5][x]);
		}
	}
}

