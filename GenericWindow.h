#pragma once
#include <iostream>
#include <string>
#include "parameters.h"
#include "Canvas.h"

class GenericWindow
{
protected:
    std::string canvas[SCREEN_HEIGHT];
    int width = SCREEN_WIDTH;
    int height = SCREEN_HEIGHT;
    char border_ch = 'X';
public:
    GenericWindow() {};
    virtual ~GenericWindow() {};
    virtual void draw(Canvas &c, int x, int y) = 0;
    int GetWidth() {return width;};
    int GetHeight() {return height;};
};