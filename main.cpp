#include <iostream>
#include "Canvas.h"
#include "Frame.h"

int main()
{
    Frame f0(16, 4, '*',' ');
    Canvas c('.');
    f0.draw(c, 1, 1);
    c.render();
    return 0;
}