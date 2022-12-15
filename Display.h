//Display.h

void timer_init();
void init();
void wait1_ms();
void wait_ms(int ms);
void wait_240nsec();
unsigned char read_lcd(int rs, int cs);
void check_bf(int cs);
void write_lcd(int rs, int cs, unsigned char data);
void reset_lcd();
void point_lcd(int x, int y);
void design_lcd(int x, int y, unsigned char data);
int point_char(int x, int page);
void design_char(int x, int page, unsigned char data);
void design_string(int x, int page, unsigned char *data_cnt, int data_len);
void design_number(int x, int page, int data);
void image0_design();
void design_image();
void LCD_light();
void design_display_char(int x, int page, unsigned char *data_cnt, int data_len);
int point_image(int x, int page);
void design_display_all();

