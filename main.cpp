#include <iostream>
#include <cstdio>
#include <ncurses.h>
#include <string>
#include "Game.h"

using namespace std;

int main()
{
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    Game g(1000);
    g.draw();
    refresh();
    getch();
    
    // Not needed, but linker crash when I remove this block
    {
    // Baner info_top_assets("                      Assets                         ", '#');
    ListWindow<Stock> assets_window(80, 10, '#', '.', 9);
    assets_window.add(Stock("Item A",150,0,100,200));
    System s;
    }

    endwin();
    return 0;
}