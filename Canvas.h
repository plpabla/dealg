#pragma once

#include <iostream>
#include <string>
#include "parameters.h"

struct Canvas
{
    std::string canvas[SCREEN_HEIGHT];

    Canvas(char fill=' ');
    void render(void);
};