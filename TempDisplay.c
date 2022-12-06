//TempDisplay.c

#include "iodefine.h"
#include "TempDisplay.h"

#include "Display.h"

#include <string.h>
#include <stdio.h>/*重要*/

#define WIDTH 32

/*温度の表示*/
void design_display_temp(int watert_temp)
{
	int line, cs, data_len;
	int x = 96;
	int i = 0;
	int page = 0;
	int digit[3];
	unsigned char str[80];

	int hundred = (watert_temp / 100) % 10;
	int ten = (watert_temp / 10) % 10;
	int one  = (watert_temp / 1) % 10;
	
	
	sprintf(str,"%d", watert_temp);
	
	
	data_len = strlen(str);
	
	digit[2] = hundred;
	digit[1] = ten;
	digit[0] = one;
	
	for(page=0; page<4; page++){
		for(line=0; line<WIDTH; line++){
			cs = point_image(x+line, page);
			write_lcd(1, cs, display_temp[10][page][line]);
		}
	}
	
	for(i = 0; i < 3; i++){
		x = x - 32;
		for(page=0; page<4; page++){
			if (data_len < (i + 1)){
				for(line=0; line<WIDTH; line++){
					cs = point_image(x+line, page);
					write_lcd(1, cs, display_temp[11][page][line]);
				}
			}else{
				for(line=0; line<WIDTH; line++){    
			        cs = point_image(x+line, page);
			        write_lcd(1, cs, display_temp[digit[i]][page][line]);
		        }
		    }
	    }
	} 
}