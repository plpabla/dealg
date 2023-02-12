#pragma once
#include <string>
#include "Frame.h"

class InputWindow: public Frame
{
    protected:
    std::string msg;

    enum {
        ROOM_FOR_INPUT = 10
    };

    public:
    InputWindow(std::string msg, char border='X'): 
        Frame(msg.length()+ROOM_FOR_INPUT, 3, border, ' '), msg(msg) {};
    virtual ~InputWindow() {};
    
    int draw(Canvas &c, int x, int y) override;
};

