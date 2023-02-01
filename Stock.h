#pragma once
#include <string>
#include <iostream>
#include "Item.h"

class Stock: public Item
{
    protected:
    int quantity;
    public:
    Stock(std::string name="", float price=0.0, int qty=0): Item(name, price), quantity(qty) {};
    ~Stock() override {};

    int getQty() {return quantity;};
};