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

    Canvas c('.');
    ListWindow<Stock> lw(20, 10, 'x', ' ');
    lw.add(Stock("Item A"));
    lw.add(Stock("Item B"));
    lw.add(Stock("Item C"));
    lw.add(Stock("Item D1"));
    lw.add(Stock("Item D2"));
    lw.add(Stock("Item E"));

    int ch=0;
    do
    {    
        if(ch==KEY_UP) lw.navigate(-1);
        if(ch==KEY_DOWN) lw.navigate(1);
        clear();
        f0.draw(c, 3, 1);
        f0.draw(c, 7, 2);
        f0.draw(c, 76, 22);
        f1.draw(c, 8, 10);
        lw.draw(c, 40, 5);

        c.render();
    } while((ch = getch()) != 'q');

    refresh();
    endwin();
    return 0;
}