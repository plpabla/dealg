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
    if(x>=SCREEN_WIDTH) return;
    if(y>=SCREEN_HEIGHT) return;

    bool is_cropped = (width+x) > SCREEN_WIDTH;
    int chars_to_be_replaced = is_cropped ? (SCREEN_WIDTH-x) : (width);
    string border_line = string(chars_to_be_replaced, border_ch);
    string line;

    if(is_cropped)
    {
        if((chars_to_be_replaced-1) > 0)
        {
            line = border_ch + string(chars_to_be_replaced-1, fill_ch);
        } else
        {
            line = string(2, border_ch);
        }
    } else
    {
        if((chars_to_be_replaced-2) > 0)
        {
            line = border_ch + string(chars_to_be_replaced-2, fill_ch) + border_ch;
        } else
        {
            line = string(chars_to_be_replaced, border_ch);
        }
    }

    cout << "Border: [" << border_line << "]\n";    
    cout << "Line:   [" << line << "]\n";

    // Top border
    int row = y;
    c.canvas[y].replace(x, chars_to_be_replaced, border_line);
    row++;
    for(; row<(height+y-1); row++)
    {
        #ifdef DEBUG
            string original_row = c.canvas[row];
        #endif

        if(row>=SCREEN_HEIGHT) return;
        c.canvas[row].replace(x, chars_to_be_replaced, line);

        #ifdef DEBUG
            cout << "Replacing " << chars_to_be_replaced << " characters:" << endl;
            cout << "  <<[" << original_row << "]" << endl;
            cout << "  >>[" << c.canvas[row] << "]" << endl;
        #endif
    }

    // Bottom border
    if(row>=SCREEN_HEIGHT) return;
    c.canvas[height+y-1].replace(x, chars_to_be_replaced, border_line);
}