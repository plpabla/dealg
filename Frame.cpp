#include <iostream>
#include "Frame.h"
#include "parameters.h"

#define DEBUG

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

    bool is_cropped = (width+x) > SCREEN_WIDTH;
    int chars_to_be_replaced = is_cropped ? (SCREEN_WIDTH-x) : (width);
    string line = string(chars_to_be_replaced, border_ch);

    for(int row=0; row<height; row++)
    {
        if((y+row)>=SCREEN_HEIGHT) break;
    #ifdef DEBUG
        cout << "Replacing " << chars_to_be_replaced << " characters:" << endl;
        cout << "  <<[" << c.canvas[y+row] << "]" << endl;
    #endif
        c.canvas[y+row].replace(x, chars_to_be_replaced, line);

    #ifdef DEBUG
        cout << "  >>[" << c.canvas[y+row] << "]" << endl;
    #endif
    }
}