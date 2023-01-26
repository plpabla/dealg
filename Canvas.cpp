#include "Canvas.h"
#include <string>

using namespace std;

Canvas::Canvas(char fill)
{
    for(auto & line: canvas)
    {
        line = string(SCREEN_WIDTH, fill);
    }
}

void Canvas::render(void)
{
    // TODO
}