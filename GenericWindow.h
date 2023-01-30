#pragma once
#include <iostream>
#include <string>
#include "parameters.h"
#include "Canvas.h"

class GenericWindow
{
protected:
    int width = SCREEN_WIDTH;
    int height = SCREEN_HEIGHT;
    char border_ch = 'X';
    char fill_ch = ' ';
public:
    GenericWindow(int w=0, int h=0, char border='x', char fill=' '): 
        width(w), height(h), border_ch(border), fill_ch(fill) {};
    virtual ~GenericWindow() {};
    virtual void draw(Canvas &c, int x, int y) = 0;
    int GetWidth() {return width;};
    int GetHeight() {return height;};
};