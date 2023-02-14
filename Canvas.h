#pragma once

#include <iostream>
#include <string>
#include "parameters.h"

struct Canvas
{
    std::string canvas[SCREEN_HEIGHT];

    Canvas(char fill=' ');
    ~Canvas() {};
    void render(void);
    void clear(void);

    private:
    char fill = ' ';
};

