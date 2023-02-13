#include <iostream>
#include <cstdio>
#include <ncurses.h>
#include <string>
#include "System.h"
#include "Canvas.h"
#include "Frame.h"
#include "ListWindow.h"
#include "Stock.h"
#include "Baner.h"
#include "InputWindow.h"

using namespace std;

int main()
{
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    Baner info_top_assets("                      Assets                         ", '#');
    Baner info_top_price("   Price  ", '#');
    Baner info_top_stock("Quantity", '#');
    Baner info_keys("   [b]uy       [s]ell        [t]ravel        [q]uit               ", ' ');
    Baner balance(" Balance:   $14000", '#');
    InputWindow input_window_test("Enter a number: ",'#');

    ListWindow<Stock> assets_window(80, 10, '#', '.', 9);
    assets_window.add(Stock("Item A",150,0,100,200));
    assets_window.add(Stock("Item B",2000,0,1000,2220));
    assets_window.add(Stock("Item C",1000,0,1000,5000));
    assets_window.add(Stock("Item D1",4000,0,40, 4000));
    assets_window.add(Stock("Item D2",2600,0, 1e3, 4e3));
    assets_window.add(Stock("Item E",11,0,10,20));
    assets_window.add(Stock("Item E2",3900,0,200, 4e3));
    assets_window.add(Stock("Item E3",299,0,100, 300));

    System s;
    s.addWindow(&info_top_assets, 0, 0);
    s.addWindow(&info_top_price, 56, 0);
    s.addWindow(&info_top_stock, 68, 0);
    s.addWindow(&assets_window, 0, 2);
    s.addWindow(&info_keys, 0, 13);
    s.addWindow(&balance, 58, 13);

    int ch=0;
    do
    {    
        clear();
        
        switch(ch)
        {   
            case 't':
                s.addWindow(&input_window_test,8,17);
                assets_window.updatePrices();
                s.draw();
                refresh();
                int n;
                n = input_window_test.getInput();
                s.removeLastWindow();
                break;

            default:
                assets_window.navigate(ch);
                s.draw();
                refresh();
        }
    } while((ch = getch()) != 'q');

    endwin();
    return 0;
}