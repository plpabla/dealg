#pragma once
#include "System.h"

class Game: public System
{
    protected:
    float budget;
    public:
    Game(float budget=0.0);

    float getBudget() {return budget;}
    void setBudget(float b) {budget=b;}
};