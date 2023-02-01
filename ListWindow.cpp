#include "ListWindow.h"

using namespace std;

void ListWindow::add(Item *i)
{
    items.push_back(i);
}

Item* ListWindow::getCurrentItem(void)
{
    return items[0];
}