#include <iostream>
#include "Canvas.h"
#include "Frame.h"
#include "ListWindow.h"
#include "Stock.h"
#include "Keys.h"

int main()
{
    Frame f0(16, 4, '*',' ');
    Frame f1(2,2,'X','X');
    Canvas c('.');
    f0.draw(c, 3, 1);
    f0.draw(c, 7, 2);
    f0.draw(c, 76, 22);
    f1.draw(c, 8, 10);

    ListWindow<Stock> lw(20, 10, 'x', ' ');
    lw.add(Stock("Item A"));
    lw.add(Stock("Item B"));
    lw.add(Stock("Item C"));
    lw.add(Stock("Item D1"));
    lw.add(Stock("Item D2"));
    lw.add(Stock("Item E"));

    lw.navigate(TKey::KEY_DOWN);
    lw.navigate(TKey::KEY_DOWN);

    lw.draw(c, 40, 5);

    c.render();
    return 0;
}