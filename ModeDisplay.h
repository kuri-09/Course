//ModeDisplay.c

void design_display_mode(int target_temp);

const unsigned char display_fixed[3][64] = {
//���[�h
  {0x00, 0x00, 0x00, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0xfc, 0xfc, 0xfc, 0xfc, 0x1c, 0x1c, 0x1c,
   0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe,
   0xfe, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x7c, 0x30, 0x2e, 0x1e, 0x1c, 0x00, 0x00},

   
  {0x00, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0xff, 0xff, 0xff, 0xff, 0x0e, 0x0e, 0x0e,
   0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x00, 0x00, 0x00, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
   0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x00, 0x00, 0x00, 0xff,
   0xff, 0xff, 0x0f, 0x0f, 0x1e, 0x1e, 0x3e, 0x3c, 0x7c, 0x78, 0xf8, 0xf0, 0x70, 0x20, 0x00, 0x00},

  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x1f, 0x1f, 0x3f, 0x3c, 0x3c, 0x3c,
   0x3c, 0x3c, 0x3c, 0x3c, 0x1c, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f,
   0x3f, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00}
};

/*�����@�ߖ�@�~���N*/
const unsigned char display_mode[3][3][64] = {
//����
 {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0xd8, 0xd8, 0x58, 0x58, 0x58, 0x5c, 0x5c, 0x5c, 0x58,
   0x58, 0x58, 0xd8, 0xd8, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x98, 0x1c, 0x38, 0x78, 0x30, 0x00,
   0xfc, 0xfc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00},

  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xf8, 0xf8, 0xf8, 0x1b, 0x1b, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb,
   0xdb, 0xdb, 0x1b, 0x1b, 0xf8, 0xf8, 0xf8, 0x00, 0x00, 0x02, 0x07, 0x87, 0xce, 0xc6, 0x00, 0xf0,
   0xf7, 0x77, 0x76, 0xf6, 0xf6, 0x76, 0xf6, 0xf6, 0x76, 0x77, 0xf7, 0xf0, 0x00, 0x00, 0x00, 0x00},
   
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x3f, 0x00, 0x00, 0x07, 0x07, 0x06, 0x06, 0x06, 0x06, 0x06,
   0x07, 0x07, 0x30, 0x30, 0x3f, 0x3f, 0x1f, 0x00, 0x00, 0x08, 0x1e, 0x3f, 0x07, 0x39, 0x18, 0x1f,
   0x1f, 0x18, 0x18, 0x1f, 0x1f, 0x18, 0x1f, 0x1f, 0x18, 0x18, 0x1f, 0x1f, 0x18, 0x38, 0x00, 0x00}},

//�ߖ�
 {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0x7c, 0x3c, 0x7c, 0xf0, 0xf0, 0x30, 0x30, 0xc0, 0xf0,
   0x7c, 0x3c, 0x3c, 0xf0, 0xf0, 0x30, 0x30, 0x30, 0x00, 0x00, 0x40, 0xe0, 0xe0, 0xf8, 0x3c, 0xcc,
   0xe0, 0xf0, 0x20, 0x80, 0xc0, 0xf8, 0xfc, 0xfc, 0xe4, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x00, 0x00}, 
   
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xdb, 0xdb, 0xdb, 0xff, 0xff, 0xff, 0x00, 0xff,
   0xff, 0xff, 0x07, 0x07, 0x07, 0xff, 0xff, 0xff, 0x00, 0x00, 0x38, 0xf8, 0xb9, 0x3f, 0xff, 0xfb,
   0x19, 0x9e, 0xfe, 0x13, 0x07, 0x1b, 0x7c, 0xf8, 0xe0, 0x80, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00},
   
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x18, 0x38, 0x3f, 0x3f, 0x18, 0x18, 0x1c, 0x0f, 0x3f, 0x3c, 0x00, 0x3f,
   0x3f, 0x3f, 0x00, 0x1c, 0x1c, 0x0f, 0x0f, 0x07, 0x00, 0x00, 0x08, 0x1f, 0x0f, 0x00, 0x3f, 0x3f,
   0x20, 0x03, 0x0f, 0x0f, 0x00, 0x00, 0x08, 0x39, 0x38, 0x38, 0x3c, 0x3f, 0x1f, 0x01, 0x00, 0x00}},

//�~���N
 {{0x00, 0x00, 0x00, 0x60, 0x78, 0x70, 0x70, 0x70, 0xf0, 0xf0, 0xf0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
   0xc0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0xfe,
   0xfe, 0xfe, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x80, 0xe0, 0xf0, 0xfe, 0x7e, 0x7e, 0x7e, 0x70, 0x70, 0x70, 0x70, 0xf0, 0xf0, 0xf0, 0xf0, 0x60}, 
   
  {0x00, 0x00, 0x00, 0x38, 0x3c, 0x3c, 0x38, 0x38, 0x38, 0x78, 0x78, 0x70, 0x70, 0xf1, 0xf1, 0xe1,
   0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0xff,
   0xff, 0xff, 0xff, 0x00, 0x00, 0x80, 0xc0, 0xf0, 0xf8, 0xf0, 0x20, 0x00, 0x08, 0x0c, 0x1e, 0x1f,
   0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xfc, 0x7f, 0x3f, 0x0f, 0x03, 0x00},
   
  {0x00, 0x0c, 0x1e, 0x1e, 0x1e, 0x1c, 0x1c, 0x3c, 0x3c, 0x3c, 0x38, 0x38, 0x78, 0x78, 0x70, 0xf0,
   0xf0, 0xf0, 0x00, 0x00, 0x10, 0x38, 0x7e, 0x7f, 0x1f, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x1f,
   0x3f, 0x3f, 0x3f, 0x1e, 0x1f, 0x0f, 0x07, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x18, 0x78, 0x7c, 0x3c, 0x3e, 0x1f, 0x0f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00}}
   
};
