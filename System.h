#pragma once
#include <vector>
#include "Canvas.h"
#include "GenericWindow.h"

class System
{
    protected:
    struct window_loc
    {
        GenericWindow* pw;
    };
    Canvas *pCanvas;
    std::vector<GenericWindow*> windows;

    public:
    System(char fill_ch=' ') {pCanvas = new Canvas(fill_ch);};
    ~System(){delete pCanvas; };
    Canvas* getCanvas(void);
    int getWindowsCount(void) {return windows.size();};
    void addWindow(GenericWindow *w, int x=0, int y=0);
    void removeLastWindow(void) {windows.pop_back();};
    void draw(void);
};