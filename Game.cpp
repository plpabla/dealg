#include "Game.h"
// #include "InputWindow.h"

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

    // TODO: I should have access to that or make it dynamically linked with a variable!!!!
    pBudget = new Baner(" Balance:   $14000", '#'); 
    windows.push_back(pBudget);
    addWindow(pBudget, 58, 13);

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
    // draw();
    // refresh();
    // getch();

    // GenericWindow* get_amount_window = new InputWindow("Travel? ");
    int ch=0;
    do
    {    
        clear();
        
        switch(ch)
        {   
            case 't':
            {
                if(current_state==state::SELECT)
                {
                    // Process only here
                    current_state = state::TRAVEL;
                    windows.push_back(pTravels);
                    addWindow(pTravels, 10, 5);
                    pCurrentWindow = pTravels;
                }
                // addWindow(get_amount_window,8,17);
                // draw();
                // refresh();
                // removeLastWindow();
                // dynamic_cast<ListWindow<Stock>*>(current_window)->updatePrices();
                // s.getLastWindow()->getInput()
                // s.removeLastWindow();
                // assets_window.updatePrices();
                // char str[20];
                // echo();
                // move(14, 18);
                // getstr(str);
                // noecho();
                break;
            }
            case 'b':
            {
                if(current_state==state::SELECT)
                {
                    current_state = state::BUY;
                    windows.push_back(pAmount);
                    addWindow(pAmount, 12, 8);
                    pCurrentWindow = pAmount;
                }
                break;
            }
            case 10:  //ENTER
            {
                switch(current_state)
                {
                    case state::TRAVEL:
                        windows.pop_back();
                        removeLastWindow();
                        pCurrentWindow = pAssets;
                        current_state = state::SELECT;
                        break;
                    case state::BUY:
                        windows.pop_back();
                        removeLastWindow();
                        pCurrentWindow = pAssets;
                        current_state = state::SELECT;
                        break;
                    case state::SELL:
                        break;
                    default:
                        break;
                }
            }
            default:
            {
                pCurrentWindow->navigate(ch);
                break;
            }
        }
        
        draw();
        refresh();
    } while((ch = getch()) != 'q');
}

void Game::keyboard_handler(int key)
{
    // int ch=0;
    // do
    // {    
    //     clear();
        
    //     switch(ch)
    //     {   
    //         case 't':
    //         // s.addWindow(&input_window_test,8,17);
    //         // s.draw();
    //         // s.removeLastWindow();
    //         // assets_window.updatePrices();
    //         // char str[20];
    //         // echo();
    //         // move(14, 18);
    //         // getstr(str);
    //         // noecho();
    //         break;

    //         default:
    //         // assets_window.navigate(ch);
    //     }
        
    //     // s.draw();
    //     // refresh();
    // } while((ch = getch()) != 'q');
}