#pragma once
#include <iostream>
#include <vector>
#include "System.h"

#include "ListWindow.h"
#include "Stock.h"


class Game: public System
{
    protected:
    float budget;
    std::vector<GenericWindow*> windows;

    public:
    Game(float budget=0.0);
    ~Game() override;

    void keyboard_handler(int key) override {};
    float getBudget() {return budget;}
    void setBudget(float b) {budget=b;}

    private:
    ListWindow<Stock>* create_assets_list(void);
};