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
    //
}