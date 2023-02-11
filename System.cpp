#include "System.h"

Canvas* System::getCanvas(void)
{
    return pCanvas;
}

void System::addWindow(GenericWindow *w, int x, int y)
{
    windows.push_back(window_loc(w, x, y));
};

void System::draw(void)
{
    for(const auto w : windows)
    {
        w.pw->draw(*pCanvas, w.x, w.y);
    }
}