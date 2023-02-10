#include <iostream>
#include <cstdio>
#include <ncurses.h>
#include "Canvas.h"
#include "Frame.h"
#include "ListWindow.h"
#include "Stock.h"
#include "Baner.h"

int main()
{
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    Baner info_top_assets("                      Assets                         ", '#');
    Baner info_top_price("   Price  ", '#');
    Baner info_top_stock("Quantity", '#');
    Baner info_keys("             [b]uy       [s]ell        [t]ravel        [q]uit               ", ' ');

    Canvas c(' ');
    ListWindow<Stock> assets_window(80, 10, '#', '.', 9);
    assets_window.add(Stock("Item A",150,0,100,200));
    assets_window.add(Stock("Item B",2000,0,1000,2220));
    assets_window.add(Stock("Item C",1000,0,1000,5000));
    assets_window.add(Stock("Item D1",4000,0,40, 4000));
    assets_window.add(Stock("Item D2",2600,0, 1e3, 4e3));
    assets_window.add(Stock("Item E",11,0,10,20));
    assets_window.add(Stock("Item E2",3900,0,200, 4e3));
    assets_window.add(Stock("Item E3",299,0,100, 300));

    int ch=0;
    do
    {    
        clear();
        assets_window.navigate(ch);

        info_top_assets.draw(c, 0, 0);
        info_top_price.draw(c, 56, 0);
        info_top_stock.draw(c, 68, 0);
        assets_window.draw(c, 0, 2);
        info_keys.draw(c,0,12);

        if(ch=='t')
        {   
            assets_window.updatePrices();
            Baner b("xxxxxx");
            b.draw(c, 10, 10);
        }

        // Baner budget_window();

        c.render();
    } while((ch = getch()) != 'q');

    refresh();
    endwin();
    return 0;
}