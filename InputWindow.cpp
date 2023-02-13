#include "InputWindow.h"
#include <string>
#include <ncurses.h>

using namespace std;

void InputWindow::draw(Canvas &c, int x, int y)
{
    this->x = x;
    this->y = y;
    Baner::draw(c, x, y);
}

int InputWindow::getInput(void)
{
    move(y+1, x+msg.length()-ROOM_FOR_INPUT+2);
    int num;
    echo();
    scanw("%d",&num);
    noecho();
    refresh();
    move(SCREEN_HEIGHT, 0);
    return num;
}