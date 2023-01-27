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
    c.canvas[y][x] = border_ch;
}