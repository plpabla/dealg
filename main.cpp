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

    Game g(10000);
    g.run();

    endwin();
    return 0;
}