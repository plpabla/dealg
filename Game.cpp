#include "Game.h"
#include "Baner.h"

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
    pw = new Baner(" Balance:   $14000", '#'); 
    windows.push_back(pw);
    addWindow(pw, 58, 13);

    pw = create_assets_list();
    windows.push_back(pw);
    addWindow(pw, 0, 2);
}

Game::~Game()
{
    for(auto &p : windows)
    {
        delete p;
    }
}