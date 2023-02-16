#pragma once
#include <iostream>
#include <string>
#include "Frame.h"

class Baner: public Frame
{
    protected:
    std::string msg;

    public:
    Baner(std::string msg = "", char border='X', int extra_chars=4): 
        Frame(msg.length()+extra_chars, 3, border, ' '), msg(msg) {};
    ~Baner() override {};

    void draw(Canvas &c, int x, int y) override;
};