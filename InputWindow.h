#pragma once
#include <string>
#include "Baner.h"

class InputWindow: public Baner
{
    enum {
        ROOM_FOR_INPUT = 6
    };

    public:
    InputWindow(std::string msg, char border='X'): 
        Baner(msg+std::string(ROOM_FOR_INPUT,' '), border) {};
    virtual ~InputWindow() {};

    int getInput(void) {return 42;};
};

