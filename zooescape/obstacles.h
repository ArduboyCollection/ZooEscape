typedef struct{
  int xpos = 128;
  int ypos = 48;
  int vx = -3;  
  int spawn = 100; // frames until spawn
  bool go = false;
  int frame = 0; // a frame for every obstacle
  bool hit = false;
} t_obstacle;

t_obstacle ob1,ob2;



const unsigned char PROGMEM obstacles[] =
{
// width, height,
16, 16,
// FRAME 00
0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x14, 0x14, 0x1c, 0x38, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x40, 0x60, 0x70, 0x58, 0x4c, 0x56, 0x53, 0x50, 0x50, 0x40, 0x40, 0x00, 
// FRAME 01
0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x1c, 0x0e, 0x07, 0x04, 0x44, 0x47, 0x58, 0x17, 0x17, 0x17, 0x57, 0x57, 0x58, 0x20, 
// FRAME 02
0x00, 0x38, 0x7e, 0x72, 0x72, 0x3e, 0xde, 0xfc, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x4d, 0x5a, 0x57, 0x17, 0x17, 0x17, 0x57, 0x5a, 0x00, 
// FRAME 03
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xf8, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x20, 0x30, 0x60, 0x66, 0x4c, 0x4c, 0x4c, 0x66, 0x60, 0x30, 0x20, 0x00, 0x00, 0x00,
};

const unsigned char PROGMEM obstacles_mask[] =
{
// width, height,
16, 16,
// FRAME 00
0x00, 0x00, 0x00, 0x00, 0x38, 0x3c, 0x3e, 0x3e, 0x3e, 0xfc, 0xf8, 0xf0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xfb, 0xf8, 0xf0, 0xe0, 0xc0, 
// FRAME 01
0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 
0x00, 0x1c, 0x3e, 0x3f, 0x0f, 0xcf, 0xef, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 
// FRAME 02
0x38, 0x7e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0x80, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xcf, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xde, 
// FRAME 03
0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf8, 0xfc, 0xf8, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x20, 0x70, 0x78, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x78, 0x70, 0x20, 0x00, 0x00,
};