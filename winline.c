
void draw_win_line(char **board, char winner){
    if(winner = 'r'){
        int x0 = my_box[win_linex_r[0] + win_liney_r[0]*8].start_pos_x;
        int y0 = my_box[win_linex_r[0] + win_liney_r[0]*8].start_pos_y;

        int x1 = my_box[win_linex_r[5] + win_liney_r[5]*8].start_pos_x;
        int y1 = my_box[win_linex_r[5] + win_liney_r[5]*8].start_pos_y;

        draw_line(x0, y0, x1, y1, 0x0);
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