#include "Baner.h"


int Baner::draw(Canvas &c, int x, int y)
{
    Frame::draw(c, x, y);

    c.canvas[y+1].replace(x+2, msg.length(), msg);

    return 0;
}