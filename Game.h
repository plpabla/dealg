#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "System.h"

#include "ListWindow.h"
#include "Stock.h"
#include "Baner.h"
#include "InputWindow.h"


class Game: public System
{
    protected:
    float budget;
    std::vector<GenericWindow*> windows;

    enum state
    {
        SELECT,
        TRAVEL,
        BUY,
        SELL,
        MESSAGE,
        EXIT_PROMPT,
    };
    state current_state;

    GenericWindow* pCurrentWindow = nullptr;
    ListWindow<Stock>* pAssets = nullptr;
    ListWindow<Stock>* pTravels = nullptr;
    Baner* pBudget = nullptr;
    Baner* pWrongAmountMsg = nullptr;
    Baner* pAreYouSureMsg = nullptr;
    InputWindow* pAmount = nullptr;
    std::string assets_filename;
    std::string cities_filename;

    public:
    Game(float budget=0.0, std::string assets_filename="", std::string cities_filename="");
    ~Game() override;
    void run(void);

    float getBudget() {return budget;}
    void setBudget(float b) {budget=b;}

    protected:
    ListWindow<Stock>* create_assets_list(void);
    ListWindow<Stock>* create_travels_list(void);

    void travel(void);
    void process_travel(void);
    void go_back_to_main_window(void);
    void go_to_wrong_amount(void);
    void buy(void);
    void sell(void);
    void exit_state(void);
};