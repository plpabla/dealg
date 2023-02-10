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
    assets_window.add(Stock("Item A"));
    assets_window.add(Stock("Item B"));
    assets_window.add(Stock("Item C",32, 8));
    assets_window.add(Stock("Item D1"));
    assets_window.add(Stock("Item D2"));
    assets_window.add(Stock("Item E"));
    assets_window.add(Stock("Item E2",200,10000));
    assets_window.add(Stock("Item E3",150,9999));

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

        // Baner budget_window();

        c.render();
    } while((ch = getch()) != 'q');

    refresh();
    endwin();
    return 0;
}