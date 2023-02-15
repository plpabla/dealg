#pragma once
#include <vector>
#include "Canvas.h"
// #include "Item.h"
#include "GenericWindow.h"

class System
{
    protected:
    struct window_loc
    {
        GenericWindow* pw;
        int x = 0;
        int y = 0;
        window_loc(GenericWindow* p, int x=0, int y=0): pw(p), x(x), y(y) {};
    };
    Canvas *pCanvas;
    std::vector<window_loc> windows;

    public:
    System(char fill_ch=' ') {pCanvas = new Canvas(fill_ch);};
    virtual ~System() { delete pCanvas; };
    Canvas* getCanvas(void);
    int getWindowsCount(void) {return windows.size();};
    void addWindow(GenericWindow *w, int x=0, int y=0);
    void removeLastWindow(void) {windows.pop_back();};
    void draw(void);
    virtual void keyboard_handler(int key) {};
};