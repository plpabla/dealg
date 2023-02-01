#pragma once
#include <vector>
#include "Item.h"

//template<typename Item_T> // TODO: consider making template
class ListWindow
{
    protected:
    std::vector<Item*> items;
    Item* current_item;

    public:
    ListWindow() {};
    virtual ~ListWindow() {};

    void navigate(char c) {};   //TODO
    void add(Item *i);          //TODO: Consider refactoring to operator+
    void removeAll(void) {};    //TODO
    Item* getCurrentItem(void); 
};