volatile int pixel_buffer_start; // global variable
void clear_screen();
void draw_line(int x0, int y0, int x1, int y1, short int color);
void plot_pixel(int x, int y, short int line_color);
void end_screen(volatile int *pixel_ctrl_ptr,int colour);

void swap(int * x, int * y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main(void)
{
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
    /* Read location of the pixel buffer from the pixel buffer controller */
    pixel_buffer_start = *pixel_ctrl_ptr;
    
    clear_screen();
    //    draw_line(0, 0, 150, 150, 0x001F);   // this line is blue
    //    draw_line(150, 150, 319, 0, 0x07E0); // this line is green
    //    draw_line(0, 239, 319, 239, 0xF800); // this line is red
    //    draw_line(319, 0, 0, 239, 0xF81F);   // this line is a pink color
    end_screen(pixel_ctrl_ptr,2);
    
    
    
    
    
    
    
    
    
    return 0;
}
void end_screen(volatile int *pixel_ctrl_ptr,int colour){
    pixel_buffer_start = *pixel_ctrl_ptr;
    
    clear_screen();
    
    
    //WINNER
    draw_line(58, 35, 76, 77, 0x0);
    draw_line(76, 77, 85, 61, 0x0);
    draw_line(85, 61, 95, 77, 0x0);
    draw_line(95, 77, 114, 32, 0x0);
    
    draw_line(122, 57, 122, 78, 0x0);
    
    draw_line(135, 57, 135, 79, 0x0);
    draw_line(135, 57, 157, 79, 0x0);
    draw_line(157, 79, 157, 56, 0x0);
    
    
    draw_line(165, 55, 165, 80, 0x0);
    draw_line(165, 55, 189, 78, 0x0);
    draw_line(189, 78, 188, 55, 0x0);
    
    draw_line(198, 55, 217, 55, 0x0);
    draw_line(198, 55, 198, 79, 0x0);
    draw_line(198, 79, 218, 79, 0x0);
    draw_line(198, 66, 217, 66, 0x0);
    
    draw_line(232, 56, 249, 56, 0x0);
    draw_line(232, 56, 232, 66, 0x0);
    draw_line(249, 56, 249, 65, 0x0);
    draw_line(232, 66, 251, 80, 0x0);
    draw_line(232, 66, 232, 79, 0x0);
    draw_line(232, 66, 249, 65, 0x0);
    
    //PRESS
    draw_line(14, 155, 14, 201, 0x0);
    draw_line(14, 155, 34, 155, 0x0);
    draw_line(34, 155, 34, 171, 0x0);
    draw_line(34, 171, 14, 172, 0x0);
    
    draw_line(29, 183, 29, 200, 0x0);
    draw_line(29, 189, 36, 182, 0x0);
    
    draw_line(44, 180, 44, 199, 0x0);
    draw_line(44, 180, 58, 181, 0x0);
    draw_line(44, 188, 58, 187, 0x0);
    draw_line(58, 181, 58, 187, 0x0);
    draw_line(44, 199, 59, 199, 0x0);
    
    draw_line(77, 178, 67, 179, 0x0);
    draw_line(67, 179, 67, 184, 0x0);
    draw_line(67, 184, 76, 185, 0x0);
    draw_line(76, 185, 76, 198, 0x0);
    draw_line(76, 198, 77, 198, 0x0);
    
    draw_line(94, 178, 85, 178, 0x0);
    draw_line(84, 178, 85, 184, 0x0);
    draw_line(85, 184, 94, 184, 0x0);
    draw_line(94, 184, 94, 198, 0x0);
    draw_line(94, 184, 94, 198, 0x0);
    draw_line(94, 198, 84, 198, 0x0);
    
    //to
    draw_line(170, 144, 214, 144, 0x0);
    draw_line(191, 145, 191, 201, 0x0);
    
    draw_line(198, 176, 209, 176, 0x0);
    draw_line(209, 176, 209, 199, 0x0);
    draw_line(209, 199, 198, 199, 0x0);
    draw_line(198, 199, 198, 176, 0x0);
    
    //KEY
    draw_line(121, 148, 121, 201, 0x0);
    draw_line(121, 173, 134, 148, 0x0);
    draw_line(121, 173, 135, 201, 0x0);
    
    draw_line(140, 181, 154, 181, 0x0);
    draw_line(154, 181, 154, 187, 0x0);
    draw_line(154, 187, 140, 188, 0x0);
    draw_line(140, 181, 140, 199, 0x0);
    draw_line(140, 199, 155, 199, 0x0);
    
    draw_line(160, 179, 167, 188, 0x0);
    draw_line(171, 178, 161, 200, 0x0);
    
    //PLAY
    draw_line(237, 142, 256, 142, 0x0);
    draw_line(256, 142, 256, 163, 0x0);
    draw_line(256, 163, 237, 164, 0x0);
    draw_line(237, 142, 237, 201, 0x0);
    
    draw_line(249, 177, 249, 200, 0x0);
    draw_line(249, 199, 256, 199, 0x0);
    
    draw_line(256, 200, 256, 177, 0x0);
    draw_line(256, 177, 270, 200, 0x0);
    draw_line(257, 191, 264, 190, 0x0);
    
    draw_line(271, 175, 281, 185, 0x0);
    draw_line(284, 175, 277, 200, 0x0);
    
    
    if(colour == 1)
    {
         draw_line(187, 103, 186, 128, 0xF800);
         draw_line(187, 103, 206, 114, 0xF800);
         draw_line(206, 114, 186, 128, 0xF800);
        
         draw_line(120, 101, 136, 100, 0xF800);
         draw_line(136, 100, 136, 115, 0xF800);
         draw_line(136, 115, 120, 115, 0xF800);
         draw_line(120, 101, 120, 130, 0xF800);
         draw_line(120, 115, 139, 130, 0xF800);
        
         draw_line(164, 102, 147, 103, 0xF800);
         draw_line(164, 115, 147, 115, 0xF800);
         draw_line(166, 128, 148, 128, 0xF800);
         draw_line(148, 128, 147, 103, 0xF800);
        
    }
    
    
    else if(colour ==2)
    {
        
        draw_line(74, 95, 89, 111, 0xEFA0);
        draw_line(100, 94, 77, 131, 0xEFA0);
        
        draw_line(120, 105, 104, 105, 0xEFA0);
        draw_line(104, 105, 104, 131, 0xEFA0);
        draw_line(104, 131, 120, 131, 0xEFA0);
        draw_line(104, 116, 120, 116, 0xEFA0);
        
        draw_line(133, 103, 133, 133, 0xEFA0);
        draw_line(133, 133, 154, 133, 0xEFA0);
        
        draw_line(165, 103, 165,134, 0xEFA0);
        draw_line(165, 134, 189, 134, 0xEFA0);
        
        draw_line(201, 103, 228, 103, 0xEFA0);
        draw_line(201, 103, 201, 132, 0xEFA0);
        draw_line(201, 132, 228, 132, 0xEFA0);
        draw_line(228, 132, 228, 103, 0xEFA0);
        
        draw_line(237, 102, 249, 129, 0xEFA0);
        draw_line(249, 129, 257, 119, 0xEFA0);
        draw_line(257, 119, 265, 129, 0xEFA0);
        draw_line(265, 129, 275, 102, 0xEFA0);
    }
}
void clear_screen() {
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

void draw_line(int x0, int y0, int x1, int y1, short int color) {
    int is_steep = 0; //initialize to false
    int abs_y = y1 - y0;
    int abs_x = x1 - x0;
    
    if (abs_y < 0 ) abs_y =-abs_y; //change sign if negative
    if (abs_x < 0) abs_x = -abs_x;
    
    if (abs_y > abs_x) is_steep=1; //TRUE
    
    if (is_steep) {
        swap(&x0, &y0);
        swap(&x1, &y1);
    }
    
    if (x0>x1) {
        swap(&x0, &x1);
        swap(&y0, &y1);
    }
    
    int deltax = x1 - x0;
    int deltay = y1-y0;
    if (deltay <0) deltay = -deltay;
    int error = -(deltax / 2);
    int y = y0;
    int y_step;
    
    if (y0 < y1) y_step =1;
    else y_step = -1;
    
    for(int x=x0; x<=x1; x++) {
        if (is_steep) plot_pixel(y,x, color);
        else plot_pixel(x,y, color);
        
        error += deltay;
        
        if (error>=0) {
            y +=y_step;
            error -= deltax;
        }
    }
}


void plot_pixel(int x, int y, short int line_color)
{
    *(short int *)(pixel_buffer_start + (y << 10) + (x << 1)) = line_color;
}

