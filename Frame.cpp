#include <iostream>
#include "Frame.h"
#include "parameters.h"

// #define DEBUG

using namespace std;

Frame::Frame(int w, int h, char border, char fill): GenericWindow(w,h,border, fill) { };

void Frame::draw(Canvas &c, int x, int y)
{
    #ifdef DEBUG
        cout << "Drawing frame at (" <<x << ", " << y << ") " << width << "x" << height << endl;
    #endif

    if(x>=SCREEN_WIDTH) return;
    if(y>=SCREEN_HEIGHT) return;

    bool border_point = true;
    bool it_is_border_line = true;
    for(int row=y; row<(y+height); row++)
    {
        if(row>=SCREEN_HEIGHT) return;
        if(row==(y+height-1)) it_is_border_line = true;

        for(int col=x; col<(x+width); col++)
        {
            // Set back to border point for the last one
            if(col==(x+width-1)) border_point=true;

            // Check if we should start a new line
            if(col>=SCREEN_WIDTH)
            {
                border_point = true;
                break;
            } 

            // Draw character (border or fill)
            c.canvas[row][col] = (border_point ? border_ch : fill_ch);
            if(!it_is_border_line) border_point=false;
        }
        border_point = true;
        it_is_border_line = false;
    }
}