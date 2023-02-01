#pragma once
#include <vector>
#include "Exceptions.h"

template<typename Item_T> 
class ListWindow
{
    protected:
    std::vector<Item_T> items;
    Item_T current_item;

    public:
    ListWindow() {};
    virtual ~ListWindow() {};

    void navigate(char c) {};   //TODO
    void add(Item_T i);         //TODO: Consider refactoring to operator+
    void removeAll(void) {};    //TODO
    Item_T getCurrentItem(void); 
};

template<typename Item_T> 
void ListWindow<Item_T>::add(Item_T i)
{
    items.push_back(i);
}

template<typename Item_T> 
Item_T ListWindow<Item_T>::getCurrentItem(void)
{
    if(items.size())
    {
        return items[0];
    }
    throw EmptyListException();
}

template<typename Item_T> 
inline bool operator==(const Item_T &lhs, const Item_T &rhs)
{
    // TODO: Make it idiot-proof (compare with no-class member)
    return lhs.getName() == rhs.getName();
}