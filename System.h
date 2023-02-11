#pragma once
#include "Canvas.h"

class System
{
    Canvas *pCanvas;
    public:
    System(char fill_ch=' ') {pCanvas = new Canvas(fill_ch);};
    ~System(){delete pCanvas; };
    Canvas* getCanvas(void);
};