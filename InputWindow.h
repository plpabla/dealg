#pragma once
#include <string>
#include "Baner.h"

class InputWindow: public Baner
{
    protected:
    enum {
        ROOM_FOR_INPUT = 6
    };
    int x = 0;
    int y = 0;

    public:
    InputWindow(std::string msg, char border='X'): 
        Baner(msg+std::string(ROOM_FOR_INPUT,' '), border) {};
    ~InputWindow() override {};
    void draw(Canvas &c, int x, int y) override;
    int getInput(void);
};

