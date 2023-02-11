#include "System.h"

Canvas* System::getCanvas(void)
{
    return pCanvas;
}

void System::addWindow(GenericWindow *w, int x, int y)
{
    windows.push_back(w);
};

void System::draw(void)
{
    for(auto w : windows)
    {
        w->draw(*pCanvas, 0, 0);
    }
}