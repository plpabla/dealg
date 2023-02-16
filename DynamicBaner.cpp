#include "DynamicBaner.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;


void DynamicBaner::draw(Canvas &c, int x, int y)
{
    Frame::draw(c, x, y);

    ostringstream msg_full;
    msg_full<<msg<<" "<<fixed<<setw(digits)<<setprecision(2)<<42.00;
    c.canvas[y+1].replace(x+2, msg_full.str().length(), msg_full.str());
}