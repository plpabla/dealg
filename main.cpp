#include <iostream>
#include <cstdio>
#include <ncurses.h>
#include "Canvas.h"
#include "Frame.h"
#include "ListWindow.h"
#include "Stock.h"

int main()
{
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();


    Frame f0(16, 4, '*',' ');
    Frame f1(2,2,'X','X');

    Canvas c(' ');
    ListWindow<Stock> lw(30, 10, 'x', '.', 4);
    lw.add(Stock("Item A"));
    lw.add(Stock("Item B"));
    lw.add(Stock("Item C",32, 8));
    lw.add(Stock("Item D1"));
    lw.add(Stock("Item D2"));
    lw.add(Stock("Item E"));
    lw.add(Stock("Item E2",200,10000));
    lw.add(Stock("Item E3",150,9999));

    ListWindow<Stock> lw2(30, 10, 'x', '.');
    lw2.add(Stock("Item A"));
    lw2.add(Stock("Item B"));
    lw2.add(Stock("Item C",32, 8));

    int ch=0;
    do
    {    
        lw.navigate(ch);
        clear();
        f0.draw(c, 3, 1);
        f0.draw(c, 7, 2);
        f0.draw(c, 76, 22);
        f1.draw(c, 8, 10);
        lw.draw(c, 40, 5);
        lw2.draw(c, 0, 15);

        c.render();
    } while((ch = getch()) != 'q');

    refresh();
    endwin();
    return 0;
}