#pragma once
#include <vector>
#include <ncurses.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <math.h>
#include "Frame.h"


template<typename Item_T> 
class ListWindow : public Frame
{
    protected:
    std::vector<Item_T> items;
    int current_item_idx = 0;
    int qty_digits;

    public:
    ListWindow(int w=SCREEN_WIDTH, int h=SCREEN_HEIGHT, 
        char border='X', char fill=' ', int ditits_for_qty=0): 
        Frame(w, h, border, fill), qty_digits(ditits_for_qty) {};
    virtual ~ListWindow() override {};

    bool navigate(int k) override;
    void add(Item_T i);         //TODO: Consider refactoring to operator+
    void removeAll(void) 
    { 
        items.clear(); 
        current_item_idx=0;
    };    
    Item_T* getCurrentItem(void); 
    int getNumberOfElements(void) {return items.size();};
    void draw(Canvas &c, int x, int y) override;
    void updatePrices(void);
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
    /* TODO - processing B/S keys */
    }
    return false;
}

template<typename Item_T> 
void ListWindow<Item_T>::updatePrices(void)
{
    for(auto & i: items)
    {
        i.updatePrice();
    }
}

template<typename Item_T> 
void ListWindow<Item_T>::draw(Canvas &c, int x, int y)
{
    constexpr int X_OFFSET = 1; 
    constexpr int Y_OFFSET = 1; 
    const int MAX_LEN = (qty_digits>0)? (this->width-qty_digits-4):(this->width-2);
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
        // draw - item
        c.canvas[current_row].replace(x+X_OFFSET, line.length(), line);

        // Create a price part
        std::ostringstream price_txt;
        price_txt << std::setprecision(2) << std::fixed << items[cnt].getPrice() << " ";
        int x_offset_price = MAX_LEN-price_txt.str().length()+1;
        // draw - price
        c.canvas[current_row].replace(x+x_offset_price, price_txt.str().length(), price_txt.str());

        // Create quantity part if applicable
        if(qty_digits)
        {
            std::ostringstream qty_txt;
            int qty=items[cnt].getQty();
            // Crop too long numbers
            if(qty<pow(10,qty_digits))
            {
                qty_txt << " " << border_ch << std::setw(qty_digits) << qty << " ";
            } else
            {
                qty_txt << " " << border_ch << std::string(qty_digits, '?') << " ";
            }
            int x_offset_qty = MAX_LEN;
            // draw - quantity
            c.canvas[current_row].replace(x+x_offset_qty, qty_txt.str().length(), qty_txt.str());
        }
    }
};
