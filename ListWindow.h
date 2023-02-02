#pragma once
#include <vector>

template<typename Item_T> 
class ListWindow
{
    protected:
    std::vector<Item_T> items;
    Item_T* current_item = nullptr;

    public:
    ListWindow() {};
    virtual ~ListWindow() {};

    void navigate(char c) {};   //TODO
    void add(Item_T i);         //TODO: Consider refactoring to operator+
    void removeAll(void) 
    { 
        items.clear(); 
        current_item=nullptr;
    };    
    Item_T* getCurrentItem(void); 
    int getNumberOfElements(void) {return items.size();};
};

template<typename Item_T> 
void ListWindow<Item_T>::add(Item_T i)
{
    items.push_back(i);
    current_item = &items[0];
}

template<typename Item_T> 
Item_T* ListWindow<Item_T>::getCurrentItem(void)
{
    return (items.size() ? current_item : nullptr);
}
