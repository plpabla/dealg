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
    GenericWindow* current_window;

    public:
    Game(float budget=0.0);
    ~Game() override;
    void run(void);

    float getBudget() {return budget;}
    void setBudget(float b) {budget=b;}

    private:
    void keyboard_handler(int key) override;
    ListWindow<Stock>* create_assets_list(void);
};