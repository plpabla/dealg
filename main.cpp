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

    endwin();
    return 0;
}