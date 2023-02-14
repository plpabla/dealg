#pragma once
#include <iostream>
#include <vector>
#include "System.h"
// #include "GenericWindow.h"
#include "ListWindow.h"
#include "Stock.h"
#include "Canvas.h"
#include "Baner.h"
// #include "Frame.h"
#include "InputWindow.h"
// #include "Item.h"
// #include "parameters.h"


class Game: public System
{
    protected:
    float budget;
    std::vector<GenericWindow*> windows;

    public:
    Game(float budget=0.0);
    ~Game();

    float getBudget() {return budget;}
    void setBudget(float b) {budget=b;}

    private:
    ListWindow<Stock>* create_assets_list(void);
};