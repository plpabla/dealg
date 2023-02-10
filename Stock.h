#pragma once
#include <string>
#include <iostream>
#include "Item.h"

class Stock: public Item
{
    protected:
    int quantity;
    public:
    Stock(std::string name="", float price=0.0, int qty=0, float price_min=0.0, float price_max=0.0): 
        Item(name, price), quantity(qty) 
        {
            // if all values are given, update accordingly
            if(price>0 && price_min>0 && price_max>0)
            {
                this->price_min = price_min;
                this->price_max = price_max;
            }
        };
    ~Stock() override {};

    int getQty() {return quantity;};
};