#pragma once
#include <vector>
#include <ncurses.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Frame.h"


template<typename Item_T> 
class ListWindow : public Frame
{
    protected:
    std::vector<Item_T> items;
    int current_item_idx = 0;

    public:
    ListWindow(int w=SCREEN_WIDTH, int h=SCREEN_HEIGHT, char border='X', char fill=' '): 
        Frame(w, h, border, fill) {};
    virtual ~ListWindow() {};

    bool navigate(int k);
    void add(Item_T i);         //TODO: Consider refactoring to operator+
    void removeAll(void) 
    { 
        items.clear(); 
        current_item_idx=0;
    };    
    Item_T* getCurrentItem(void); 
    int getNumberOfElements(void) {return items.size();};
    void draw(Canvas &c, int x, int y) override;
};

template<typename Item_T> 
void ListWindow<Item_T>::add(Item_T i)
{
    items.push_back(i);
    current_item_idx = 0;
}

template<typename Item_T> 
Item_T* ListWindow<Item_T>::getCurrentItem(void)
{
    return (items.size() ? (&items[current_item_idx]) : nullptr);
}

template<typename Item_T> 
bool ListWindow<Item_T>::navigate(int k)
{
    switch(k)
    {
    case KEY_DOWN:
        if(current_item_idx<(items.size()-1)) current_item_idx++;
        return true;
    case KEY_UP:
        if(current_item_idx>0) current_item_idx--;
        return true;
    }
    return false;
}

template<typename Item_T> 
void ListWindow<Item_T>::draw(Canvas &c, int x, int y)
{
    constexpr int X_OFFSET = 1; 
    constexpr int Y_OFFSET = 1; 
    const int MAX_LEN = this->width - 2;
    const int MAX_ITEMS = this->height - 2;
    const std::string SELECTED = "> ";
    const std::string NOT_SELECTED = "  ";

    Frame::draw(c, x, y);
    std::string line;
    for(int cnt=0; cnt<items.size(); cnt++)
    {
        if(cnt>=MAX_ITEMS) break;
        int current_row = y+cnt+Y_OFFSET;

        // Create line with MAX_LEN
        line = ((cnt==current_item_idx) ? SELECTED:NOT_SELECTED) + items[cnt].getName();
        line = line.substr(0, MAX_LEN);

        // Create a price part
        std::ostringstream price_txt;
        price_txt << std::setprecision(2) << std::fixed << items[cnt].getPrice() << " ";
        int x_offset_price = MAX_LEN-price_txt.str().length()+1;

        // draw - item
        c.canvas[current_row].replace(x+X_OFFSET, line.length(), line);
        // draw - price
        c.canvas[current_row].replace(x+x_offset_price, price_txt.str().length(), price_txt.str());
    }
};
