#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/*~~~~~Structures and globals~~~~~*/
struct box {
    int box_id;
    int start_pos_x;
    int end_pos_x;
    int start_pos_y;
    int end_pos_y;
    int colour;// 0-nothing 1-red 2-yellow
    
};
int startcol = 0;
int endrow = 0;
volatile int pixel_buffer_start;
struct box my_box[80];
// MAKE 56 20x20 arrays and merge them into a single one in the one below
//They have to be in order from top left to top right and from up to down
//our map pixel color database
int color_array_red[44800]={
    /*Pixel format: Red: 5 bit, Green: 6 bit, Blue: 5 bit*/
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x27, 0xf2, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    
  
    
    
};

int color_array_black[44800]={
    
    /*Pixel format: Red: 5 bit, Green: 6 bit, Blue: 5 bit*/
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    
};

int color_array_yellow[44800]={
    /*Pixel format: Red: 5 bit, Green: 6 bit, Blue: 5 bit*/
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0x67, 0xff, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    
    
    
};

int color_array_legs[44800]={
    
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24,
    
    
    
};
int animation_row;
int animation_col;
volatile int* sw = 0xFF200040;
volatile int *ledr = 0xFF200000;
volatile int *edge_cap = 0xFF20005C;
int col_Select;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


/*~~~~~Function Prototypes~~~~~*/
char** board_set_up(int y, int x);
void destroy_board(char **board);
bool check_legal(int potential_col, char **board, int y, int x);
char** update_game_board(int user_move, char **board, int y, char turn);
bool check_win_state(char ** board, int y, int x);
void print_board(char **board);
int get_col_input(int sw_in);
void clear_screen();
void plot_pixel(int x, int y, short int line_color);
void swap(int * a, int * b);
void assign_animation(int  a, int  b,volatile int *pixel_ctrl_ptr,int colour);
void resetboard(volatile int *pixel_ctrl_ptr);
void draw_box_coloured(struct box box_num);
void draw_box_coloured_red(struct box box_num);
void draw_box_coloured_yellow(struct box box_num);
void draw_box_coloured_legs(struct box box_num);
void load_map(int map_id);
void wait_for_vsync();
/*~~~~~~~~~~~~~~~~~~~~~~~ */


int main(void){
    char** board = board_set_up(7, 8);
    char turn = 'r';
    int colour = 0;
    int reset_edge = 0xFFFFFFFF;
    int edge_value;

    //Reset the edge capture for the push buttons
    *edge_cap = reset_edge;

    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
    int checker = 0;
    
    /* set front pixel buffer to start of FPGA On-chip memory */
    *(pixel_ctrl_ptr + 1) = 0xC8000000; // first store the address in the
    // back buffer
    /* now, swap the front/back buffers, to set the front buffer location */
    wait_for_vsync();
    /* initialize a pointer to the pixel buffer, used by drawing functions */
    pixel_buffer_start = *pixel_ctrl_ptr;
    clear_screen(); // pixel_buffer_start points to the pixel buffer
    /* set back pixel buffer to start of SDRAM memory */
    *(pixel_ctrl_ptr + 1) = 0xC0000000;
    pixel_buffer_start = *(pixel_ctrl_ptr + 1); // we draw on the back buffer

    load_map(0);

    resetboard(pixel_ctrl_ptr);

    while(!check_win_state(board, 7, 8)){
        if(turn == 'r'){
            colour = 1;
        }
        else{
            colour = 2;
        }

        //Check if a keybutton has been pressed
        edge_value = *edge_cap;
        while(edge_value == 0){
            //Stays here until the key is released
            edge_value = *edge_cap;
        }
        *edge_cap = reset_edge;
        edge_value = *edge_cap;

        col_Select = get_col_input(*sw);
        
        //Check if the move is legal
        while(!check_legal(col_Select, board, 7, 8)){

            while(*edge_cap == 0){
            //Stays here until the key is released
            edge_value = *edge_cap;
            }
            *edge_cap = reset_edge;
            edge_value = *edge_cap;
            col_Select = get_col_input(*sw);
        }

        update_game_board(col_Select, board, 7, turn);

        assign_animation(animation_col, animation_row, pixel_ctrl_ptr, colour);

        if(turn == 'r'){
            turn = 'y';
        }
        else{
            turn = 'r';
        }
    }

    print_board(board);
    printf("Winner!");


    destroy_board(board);
    return 0;
}

/*~~~~~Functions~~~~~*/
//Sets up the intial board data structure and sets
//each entry to empty ('e')
char** board_set_up(int y, int x){
    char** initial_board = malloc(y * sizeof(char*));

    for(int i = 0; i < y; i++){
        initial_board[i] = malloc(x * sizeof(char*));
    }

    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){

            //'e' means the spot is empty  
            initial_board[i][j] = 'o';
        }
    }

    return initial_board;
}


//De-allocates the board data structure
void destroy_board(char **board){
    free(*board);
    free(board);

    return;
}


//Checks if the user is alloowed to place their
//token into a given column, returns true if the move is valid
bool check_legal(int potential_col, char **board, int y, int x){
    //Check the column for any open spaces
    for(int i = 0; i < y; i++){
        if(board[i][potential_col] == 'o'){
            return true;
        }
    }

    //If there are no open spaces in a column then return false
    return false;
}


//Updates the game board for a given user input
char** update_game_board(int user_move, char **board, int y, char turn){

    for(int i = y - 1; i >= 0; i--){
        if(board[i][user_move] == 'o'){
            board[i][user_move] = turn;
            animation_col = user_move;
            animation_row = i;
            return board;
        }
    }

    return board;
}


//Checks the win state of the board and returns true or false
bool check_win_state(char ** board, int y, int x){
    int count_red = 0;
    int count_yellow = 0;

    //Check horizonal cases
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
            //Check for red
            if(board[i][j] == 'r'){
                count_red++;
            }
            else{
                count_red = 0;
            }
            
            //Check for yellow
            if(board[i][j] == 'y'){
                count_yellow++;
            }
            else{
                count_yellow = 0;
            }

            if(count_red >= 5 || count_yellow >= 5){
                return true;
            }
        }
    }

    //Reset counter
    count_red = 0;
    count_yellow = 0;

    //Check vertical cases
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            //Check for red
            if(board[j][i] == 'r'){
                count_red++;
            }
            else{
                count_red = 0;
            }
            
            //Check for yellow
            if(board[j][i] == 'y'){
                count_yellow++;
            }
            else{
                count_yellow = 0;
            }

            if(count_red >= 5 || count_yellow >= 5){
                return true;
            }
        }
    }

    //Reset counter
    count_red = 0;
    count_yellow = 0;
    
    //Check diagonal cases
    //Case 1: top left to bottom right lower half
    for(int diagStart = 0; diagStart < 3; diagStart++){
        
        int row, col;
        for(row = diagStart, col = 0; row < y && col < x; row++, col++){
            //Check for red
            if(board[row][col] == 'r'){
                count_red++;
            }
            else{
                count_red = 0;
            }
            
            //Check for yellow
            if(board[row][col] == 'y'){
                count_yellow++;
            }
            else{
                count_yellow = 0;
            }

            if(count_red >= 5 || count_yellow >= 5){
                return true;
            }
        }
    }

    //Reset counter
    count_red = 0;
    count_yellow = 0;

    //Case 2: top left to bottom right upper half
    for(int diagStart = 1; diagStart < 4; diagStart++){

        int row, col;
        for(row = 0, col = diagStart; row < y && col < x; row++, col++){
            //Check for red
            if(board[row][col] == 'r'){
                count_red++;
            }
            else{
                count_red = 0;
            }
            
            //Check for yellow
            if(board[row][col] == 'y'){
                count_yellow++;
            }
            else{
                count_yellow = 0;
            }

            if(count_red >= 5 || count_yellow >= 5){
                return true;
            }
        }
    }

    //Reset counter
    count_red = 0;
    count_yellow = 0;

    //Case 3: top right to bottom left lower half
    for(int diagStart = 0; diagStart > 3; diagStart--){

        int row, col;
        for(row = diagStart, col = x - 1; row < y  && col > 0; row++, col--){
            //Check for red
            if(board[row][col] == 'r'){
                count_red++;
            }
            else{
                count_red = 0;
            }
            
            //Check for yellow
            if(board[row][col] == 'y'){
                count_yellow++;
            }
            else{
                count_yellow = 0;
            }

            if(count_red >= 5 || count_yellow >= 5){
                return true;
            }
        }
    }

    //Reset counter
    count_red = 0;
    count_yellow = 0;

    //Case 4: top right to bottom left upper half
    for(int diagStart = 6; diagStart > 3; diagStart--){

        int row, col;
        for(row = 0, col = diagStart; row > y && col > 0; row++, col--){
            //Check for red
            if(board[row][col] == 'r'){
                count_red++;
            }
            else{
                count_red = 0;
            }
            
            //Check for yellow
            if(board[row][col] == 'y'){
                count_yellow++;
            }
            else{
                count_yellow = 0;
            }

            if(count_red >= 5 || count_yellow >= 5){
                return true;
            }
        }
    }
    return false;
}


//Prints the board to the terminal, for debugging
void print_board(char **board){
  for(int i = 0; i < 7; i++){
      for(int j = 0;  j <  8; j++){
        printf("%c ", board[i][j]);
      } 
      printf("\n");
    }
    printf("\n\n");
}


//Converts the binary inputs from the sw to usable values
int get_col_input(int sw_in){
    int power = 0;

    while(sw_in != 0){
        sw_in = sw_in/2;

        if(sw_in == 0){
            break;
        }

        power++;
    }

    return power;
}

//initialize
void load_map(int map_id)
{
    int numrows=9;
    int numcols=8;
    int shift_x = 60;
    int shift_y = 20;
    int block_size = 20;
    for (int index_x = 0; index_x < numcols; index_x++)   //cols
    {
        for (int index_y =0; index_y < numrows; index_y++)  ///rows
        {
            my_box[numcols*index_y+index_x].start_pos_x = shift_x+index_x*block_size;
            my_box[numcols*index_y+index_x].end_pos_x = shift_x+(index_x+1)*block_size-1;
            my_box[numcols*index_y+index_x].start_pos_y = shift_y+index_y*block_size;
            my_box[numcols*index_y+index_x].end_pos_y = shift_y+(index_y+1)*block_size-1;
            my_box[numcols*index_y+index_x].box_id = numcols*index_y+index_x;
            my_box[numcols*index_y+index_x].colour = 0;
        }
    }
    
    
}

//function to clear the screen
void clear_screen(){
    int x = 0;
    int y = 0;
    
    //draw black everywhere
    for(x = 0; x < 320; x++){
        for(y = 0; y < 200; y++){
            plot_pixel(x, y, 0xFFFF);
        }
    }

    for(x = 0; x < 320; x++){
        for(y = 200; y < 240; y++){
            plot_pixel(x, y, 0x5061);
        }
    }
}

//function to plot a line
void draw_box_coloured(struct box box_num)
{
    int count=0;
    for (int y = box_num.start_pos_y; y <= box_num.end_pos_y; y++)
    {
        for (int x = box_num.start_pos_x; x <= box_num.end_pos_x; x++)
        {
            plot_pixel(x, y, (color_array_black[count+1])*16*16+color_array_black[count]);
            count=count+2;
        }
    }
}

void draw_box_coloured_red(struct box box_num)
{
    int count=0;
    for (int y = box_num.start_pos_y; y <= box_num.end_pos_y; y++)
    {
        for (int x = box_num.start_pos_x; x <= box_num.end_pos_x; x++)
        {
            plot_pixel(x, y, (color_array_red[count+1])*16*16+color_array_red[count]);
            count=count+2;
        }
    }
}

void draw_box_coloured_yellow(struct box box_num)
{
    int count=0;
    for (int y = box_num.start_pos_y; y <= box_num.end_pos_y; y++)
    {
        for (int x = box_num.start_pos_x; x <= box_num.end_pos_x; x++)
        {
            plot_pixel(x, y, (color_array_yellow[count+1])*16*16+color_array_yellow[count]);
            count=count+2;
        }
    }
}

void draw_box_coloured_legs(struct box box_num)
{
    int count=0;
    for (int y = box_num.start_pos_y; y <= box_num.end_pos_y; y++)
    {
        for (int x = box_num.start_pos_x; x <= box_num.end_pos_x; x++)
        {
            plot_pixel(x, y, (color_array_legs[count+1])*16*16+color_array_legs[count]);
            count=count+2;
        }
    }
}

//function swaping two numbers by interchanging their adresses
void swap(int * a, int * b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void assign_animation(int  a, int  b ,volatile int * pixel_ctrl_ptr,int colour){
    startcol=a;
    endrow=b;
    clear_screen();
    int checker=startcol;
    
    int looper=0;
    
    
    while (looper<=endrow)
    {
        clear_screen();
        for(int i=0;i<72;i++)
        {
            if((i>=57 && i<=62) || (i>=65 && i<=70))
                continue;
            if(i==56  || i==64   || i==63 || i==71 )
            {
                draw_box_coloured_legs(my_box[i]);
                continue;
                
            }
            if(colour==1)
            {
            if(i==checker || my_box[i].colour==1)
                draw_box_coloured_red(my_box[i]);
            else if(my_box[i].colour==2)
                draw_box_coloured_yellow(my_box[i]);
            else
                draw_box_coloured(my_box[i]);
            }
            else if(colour==2)
            {
                if( my_box[i].colour==1)
                    draw_box_coloured_red(my_box[i]);
                else if(i==checker || my_box[i].colour==2)
                    draw_box_coloured_yellow(my_box[i]);
                else
                    draw_box_coloured(my_box[i]);
            }
            else if(colour==0)
            {
                if( my_box[i].colour==1)
                    draw_box_coloured_red(my_box[i]);
                else if(my_box[i].colour==2)
                    draw_box_coloured_yellow(my_box[i]);
                else if(i==checker || my_box[i].colour==0)
                    draw_box_coloured(my_box[i]);
            }
        }
        if(checker!=startcol +8*endrow)
            checker=checker+8;
        if(checker==startcol +8*endrow && colour==1)
            my_box[checker].colour=1;
        
        else if(checker==startcol +8*endrow && colour==2)
            my_box[checker].colour=2;
        
        else if(checker==startcol +8*endrow && colour==0)
            my_box[checker].colour=0;
        
        wait_for_vsync(); // swap front and back buffers on VGA vertical sync
        pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer
        
        looper++;
    } 
}


//function to plot a single pixel
void plot_pixel(int x, int y, short int line_color){
    *(short int *)(pixel_buffer_start + (y << 10) + (x << 1)) = line_color;
}

//
void wait_for_vsync(){
    volatile int * pixel_ctrl_ptr = 0xFF203020; // pixel controller
    register int status;
    *pixel_ctrl_ptr = 1; // start the synchronization process
    status = *(pixel_ctrl_ptr + 3);

    while ((status & 0x01) != 0) {
        status = *(pixel_ctrl_ptr + 3);
    }
}

//
void resetboard(volatile int *pixel_ctrl_ptr){
    for(int i=0;i<56;i++)
    {
        draw_box_coloured(my_box[i]);
        my_box[i].colour = 0;
    }
    wait_for_vsync(); // swap front and back buffers on VGA vertical sync
    pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer
}
/*~~~~~~~~~~~~~~~~~~~*/