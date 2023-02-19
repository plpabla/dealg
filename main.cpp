#include <iostream>
#include <cstdio>
#include <ncurses.h>
#include <string>
#include "Game.h"

using namespace std;


int main()
{
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    attron(COLOR_PAIR(1));

    raw();
    keypad(stdscr, TRUE);
    noecho();

    Game g(10000);
    g.run();

    endwin();
    return 0;
}
