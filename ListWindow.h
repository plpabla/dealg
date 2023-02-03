#pragma once
#include <vector>
#include "Frame.h"


template<typename Item_T> 
class ListWindow : public Frame
{
    protected:
    std::vector<Item_T> items;
    Item_T* current_item = nullptr;

    public:
    ListWindow(int w=SCREEN_WIDTH, int h=SCREEN_HEIGHT, char border='X', char fill=' '): 
        Frame(w, h, border, fill) {};
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
    void draw(Canvas &c, int x, int y) override;
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


template<typename Item_T> 
void ListWindow<Item_T>::draw(Canvas &c, int x, int y)
{
    constexpr int X_OFFSET = 1; 
    constexpr int Y_OFFSET = 1; 
    const int MAX_LEN = this->width - 2;

    Frame::draw(c, x, y);
    std::string line;
    for(int cnt=0; cnt<items.size(); cnt++)
    {
        // Create line with MAX_LEN
        int current_row = y+cnt+Y_OFFSET;    
        line = "> " + items[cnt].getName();
        line = line.substr(0, MAX_LEN);

        //
        c.canvas[current_row].replace(x+X_OFFSET, line.length(), line);
    }
}
