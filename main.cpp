#include <iostream>
#include "Canvas.h"
#include "Frame.h"

int main()
{
    Frame f0(16, 4, '*',' ');
    Frame f1(2,2,'X','X');
    Canvas c('.');
    f0.draw(c, 3, 1);
    f0.draw(c, 7, 2);
    f0.draw(c, 76, 22);
    f1.draw(c, 8, 10);

    c.render();
    return 0;
}