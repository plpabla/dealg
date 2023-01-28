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

    for(int row=y; row<(height+y); row++)
    {
        #ifdef DEBUG
            string original_row = c.canvas[row];
        #endif

        if(row>=SCREEN_HEIGHT) break;
        c.canvas[row].replace(x, chars_to_be_replaced, line);

        #ifdef DEBUG
            cout << "Replacing " << chars_to_be_replaced << " characters:" << endl;
            cout << "  <<[" << original_row << "]" << endl;
            cout << "  >>[" << c.canvas[row] << "]" << endl;
        #endif
    }
}