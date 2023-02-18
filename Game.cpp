#include "Game.h"
#include "DynamicBaner.h"

ListWindow<Stock>* Game::create_assets_list(void)
{
    ListWindow<Stock> *pw = new ListWindow<Stock> (80, 10, '#', '.', 9);
    pw->add(Stock("Item A",150,0,100,200));
    pw->add(Stock("Item B",2000,0,1000,2220));
    pw->add(Stock("Item C",1000,0,1000,5000));
    pw->add(Stock("Item D1",4000,0,40, 4000));
    pw->add(Stock("Item D2",2600,0, 1e3, 4e3));
    pw->add(Stock("Item E",11,0,10,20));
    pw->add(Stock("Item E2",3900,0,200, 4e3));
    pw->add(Stock("Item E3",299,0,100, 300));
    return pw;
}

Game::Game(float budget): System(), budget(budget) 
{
    current_state = state::SELECT;

    GenericWindow *pw = new Baner("                      Assets                         ", '#');
    windows.push_back(pw);
    addWindow(pw, 0, 0);

    pw = new Baner("   Price  ", '#');
    windows.push_back(pw);
    addWindow(pw, 56, 0);

    pw = new Baner("Quantity", '#');
    windows.push_back(pw);
    addWindow(pw, 68, 0);

    pw = new Baner("   [b]uy       [s]ell        [t]ravel        [q]uit               ", ' ');
    windows.push_back(pw);
    addWindow(pw, 0, 13);

    pBudget = new DynamicBaner(" Balance: ", '#', &this->budget, 10); 
    windows.push_back(pBudget);
    addWindow(pBudget, 55, 13);

    pAssets = create_assets_list();
    pCurrentWindow = pAssets;
    windows.push_back(pAssets);
    addWindow(pAssets, 0, 2);

    // Not displayed windows
    pTravels = new ListWindow<Stock>(60, 8, '#', ' ');
    pTravels->add(Stock("City A",150,0,100,200));
    pTravels->add(Stock("City B",150,0,100,200));
    pTravels->add(Stock("City C",150,0,100,200));
    pTravels->add(Stock("City D",150,0,100,200));

    pAmount = new InputWindow("Enter quantity ");

    pWrongAmountMsg = new Baner("Wrong amount. Press ENTER to continue.", '#');
}

Game::~Game()
{
    for(auto &p : windows)
    {
        delete p;
    }
}

void Game::run(void)
{
    int ch=0;
    do
    {    
        clear();
        switch(ch)
        {   
            case 't':
                if(current_state==state::SELECT) travel();
                break;

            case 'b':
                if(current_state==state::SELECT) buy();
                break;

            case 's':
                if(current_state==state::SELECT) sell();

            case 10:  //ENTER
                switch(current_state) 
                {
                    case state::TRAVEL:
                    case state::MESSAGE:
                        go_back_to_main_window();
                        break;
                }

            default:
                pCurrentWindow->navigate(ch);
                break;
        }   
        draw();
        refresh();
    } while((ch = getch()) != 'q');
}

void Game::travel(void)
{
    current_state = state::TRAVEL;
    windows.push_back(pTravels);
    addWindow(pTravels, 10, 5);
    pCurrentWindow = pTravels;

    // For tests only
    this->budget -= 1000;
}

void Game::go_back_to_main_window(void)
{
    windows.pop_back();
    removeLastWindow();
    pCurrentWindow = pAssets;
    current_state = state::SELECT;
}

void Game::go_to_wrong_amount(void)
{
    windows.push_back(pWrongAmountMsg);
    addWindow(pWrongAmountMsg, 12, 5);
    pCurrentWindow = pWrongAmountMsg;
    current_state = state::MESSAGE;
}

void Game::buy(void)
{
    addWindow(pAmount, 12, 8);
    pCurrentWindow = pAmount;
    draw();
    refresh();
    int n = pAmount->getInput();

    clear();
    removeLastWindow();

    Stock* item = pAssets->getCurrentItem();
    if(n>0 && budget>=(n*item->getPrice()))
    {
        item->operator+=(n);
        budget-=n*item->getPrice();
        pCurrentWindow = pAssets;
        current_state = state::SELECT;
    }else
    {
        go_to_wrong_amount();
    }
}

void Game::sell(void)
{
    addWindow(pAmount, 12, 8);
    pCurrentWindow = pAmount;
    draw();
    refresh();
    int n = pAmount->getInput();
    clear();
    removeLastWindow();

    Stock* item = pAssets->getCurrentItem();
    if(n>0 && n<=item->getQty())
    {
        item->operator-=(n);
        budget+=n*item->getPrice();
        pCurrentWindow = pAssets;
        current_state = state::SELECT;
    } else
    {
        go_to_wrong_amount();
    }


}


