#include "Canvas.h"
#include <string>
#include <ncurses.h>

using namespace std;

Canvas::Canvas(char fill): fill(fill)
{
    clear();
}

void Canvas::render(void)
{
    for(auto line: canvas)
    {
        line += "\n";
        printw(line.c_str());
    }
}

void Canvas::clear(void)
{
    for(auto & line: canvas)
    {
        line = string(SCREEN_WIDTH, fill);
    }
}