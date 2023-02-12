#pragma once
#include <iostream>
#include <string>
#include "Frame.h"

class Baner: public Frame
{
    protected:
    std::string msg;

    public:
    Baner(std::string msg = "", char border='X'): 
        Frame(msg.length()+4, 3, border, ' '), msg(msg) {};
    virtual ~Baner() {};

    void draw(Canvas &c, int x, int y) override;
};