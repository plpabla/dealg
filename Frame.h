#pragma once
#include <iostream>
#include "GenericWindow.h"
#include "parameters.h"

class Frame: public GenericWindow
{
    public:
    Frame(int w=SCREEN_WIDTH, int h=SCREEN_HEIGHT, char border='X', char fill=' ');
    ~Frame() override {};
    void draw(Canvas &c, int x, int y) override;
    bool navigate(int k) override {return false;};
};