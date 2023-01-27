#include <iostream>
#include "Frame.h"
#include "parameters.h"

using namespace std;

Frame::Frame(int w, int h, char border)
{
    this->border_ch = border;
    this->width = w;
    this->height = h;
}

void Frame::draw(Canvas &c, int x, int y)
{
    if(x>=SCREEN_WIDTH) return;
    if(y>=SCREEN_HEIGHT) return;

    for(int x_cnt = 0; x_cnt<width; x_cnt++)
    {
        c.canvas[y][x+x_cnt] = border_ch;
    }
}