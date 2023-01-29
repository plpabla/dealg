#include <iostream>
#include "Frame.h"
#include "parameters.h"

#define DEBUG

using namespace std;

Frame::Frame(int w, int h, char border, char fill)
{
    this->width = w;
    this->height = h;
    this->border_ch = border;
    this->fill_ch = fill;
}

void Frame::draw(Canvas &c, int x, int y)
{
    cout << "Drawing frame at (" <<x << ", " << y << ") " << width << "x" << height << endl;
    if(x>=SCREEN_WIDTH) return;
    if(y>=SCREEN_HEIGHT) return;

    bool border = true;
    bool border_line = true;
    for(int row=y; row<(y+height); row++)
    {
        if(row>=SCREEN_HEIGHT) return;
        for(int col=x; col<(x+width); col++)
        {
            // Check if we should start a new line
            if(col>=SCREEN_WIDTH)
            {
                border = true;
                break;
            } 
            c.canvas[row][col] = (border ? border_ch : fill_ch);
            if(!border_line) border=false;
            if(col==(x+width-2)) border=true;
        }
        border = true;
        border_line = false;
        if(row==(y+height-2)) border_line = true;
    }
}