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
    const float SELL_PRICE_IN_PERCENT_OF_BUY_PRICE = 0.9;
    const float BUDGET_THRESHOLD_TO_WIN_THE_GAME = 1e6;
    std::vector<GenericWindow*> windows;

    enum state
    {
        SELECT,
        TRAVEL,
        BUY,
        SELL,
        MESSAGE,
        EXIT_PROMPT,
        END_OF_GAME_PROMPT,
    };
    state current_state;

    GenericWindow* pCurrentWindow = nullptr;
    ListWindow<Stock>* pAssets = nullptr;
    ListWindow<Stock>* pTravels = nullptr;
    Baner* pBudget = nullptr;
    Baner* pWrongAmountMsg = nullptr;
    Baner* pAreYouSureMsg = nullptr;
    Baner* pYouLostMsg = nullptr;
    Baner* pYouWonMsg = nullptr;
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
    void read_assets_from_file(ListWindow<Stock> *pw, std::string filename);

    void travel(void);
    void process_travel(void);
    void go_back_to_main_window(void);
    void go_to_wrong_amount(void);
    void buy(void);
    void sell(void);
    void exit_state(void);
    void check_if_game_is_lost(void);
    void check_if_game_is_won(void);
};