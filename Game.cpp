#include "Game.h"
#include "DynamicBaner.h"

#include <fstream>
#include <sstream>

using namespace std;

ListWindow<Stock>* Game::create_assets_list(void)
{
    ListWindow<Stock> *pw = new ListWindow<Stock> (80, 10, '#', '.', 9);
    if(assets_filename=="")
    {
        pw->add(Stock("Item A",150,0,100,200));
        pw->add(Stock("Item B",2000,0,1000,2220));
        pw->add(Stock("Item C",1000,0,1000,5000));
        pw->updatePrices();
        return pw;
    } else
    {
        read_assets_from_file(pw, assets_filename);
        pw->updatePrices();
        return pw;
    }
}

ListWindow<Stock>* Game::create_travels_list(void)
{
    ListWindow<Stock> *pw = new ListWindow<Stock> (35, 8, '#', ' ');
    if(cities_filename=="")
    {
        pw->add(Stock("Krakow",400,0, 250, 400));
        pw->add(Stock("Munich",290,0, 250, 400));
        pw->add(Stock("Rome",320,0, 250, 400));
        return pw;
    } else
    {
        read_assets_from_file(pw, cities_filename);
        pw->updatePrices();
        return pw;
    }
}

void Game::read_assets_from_file(ListWindow<Stock> *pw, std::string filename)
{
    ifstream fs(filename, ios::in);
    if(!fs)
    {
        cout<<"    Not possible to open "<< filename << endl;
        cout<<"    rdstate: "<< fs.rdstate() <<endl;
        delete pw;
        pw = nullptr;
        return;
    }

    string raw_line;
    istringstream stream_line;
    string name;
    float vmin, vmax;
    char dummy;
    while(getline(fs, raw_line))
    {
        try
        {
            stream_line.clear();
            stream_line.str(raw_line);
            stream_line>>name>>vmin>>dummy>>vmax;
        }
        catch(const std::exception& e)
        {
            cerr << e.what() << '\n';
            cerr<<"Error during processing line: ["<<raw_line<<"]"<<endl;
            fs.close();
            delete pw;
            pw = nullptr;
            return;
        }
        pw->add(Stock(name,0,0,vmin,vmax));
    }
    fs.close();
}


Game::Game(float budget, string assets_filename, string cities_filename): 
    System(), 
    budget(budget),
    assets_filename(assets_filename),
    cities_filename(cities_filename)
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
    pTravels = create_travels_list();
    windows.push_back(pTravels);

    pAmount = new InputWindow("Enter quantity ");
    windows.push_back(pAmount);

    pWrongAmountMsg = new Baner("Insufficient resources. Press ENTER to continue.", '#');
    windows.push_back(pWrongAmountMsg);

    pAreYouSureMsg = new Baner("Are you sure? [y]/[n]", '#');
    windows.push_back(pAreYouSureMsg);
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
                break;

            case 10:  //ENTER
                switch(current_state) 
                {
                    case state::TRAVEL:
                        process_travel();
                        break;
                    case state::MESSAGE:
                        go_back_to_main_window();
                        break;
                }
                break;

            case 'q':
                switch(current_state) 
                {
                    case state::TRAVEL:
                    case state::MESSAGE:
                    case state::EXIT_PROMPT:
                        go_back_to_main_window();
                        break;
                    default:
                        exit_state();
                }
                break;
            
            case 'y':
                if(current_state==state::EXIT_PROMPT) return;
                break;
            
            case 'n':
                if(current_state==state::EXIT_PROMPT) go_back_to_main_window();
                break;            

            default:
                pCurrentWindow->navigate(ch);
                break;
        }   
        draw();
        refresh();
        ch = getch();
    } while(true);
}

void Game::travel(void)
{
    current_state = state::TRAVEL;
    addWindow(pTravels, 10, 5);
    pCurrentWindow = pTravels;
}

void Game::process_travel(void)
{
    float travel_price = pTravels->getCurrentItem()->getPrice();
    if(travel_price<=budget)
    {
        budget -= travel_price;
        pTravels->updatePrices();
        pAssets->updatePrices();
        go_back_to_main_window();
    } else
    {
        go_back_to_main_window();
        go_to_wrong_amount();
    }
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
    addWindow(pWrongAmountMsg, 12, 5);
    pCurrentWindow = pWrongAmountMsg;
    current_state = state::MESSAGE;
}

void Game::exit_state(void)
{
    addWindow(pAreYouSureMsg, 12, 5);
    pCurrentWindow = pAreYouSureMsg;
    current_state = state::EXIT_PROMPT;
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


