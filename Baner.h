#pragma once
#include <iostream>
#include <string>
#include "Frame.h"

class Baner: public Frame
{
    protected:
    std::string msg;

    public:
    Baner(int w=SCREEN_WIDTH, int h=SCREEN_HEIGHT, 
        char border='X', std::string msg = "", char fill=' '): 
        Frame(w, h, border, fill), msg(msg) {};
    virtual ~Baner() {};

    void draw(Canvas &c, int x, int y) override;
};