#include <string>
#include "Item.h"

class Stock: public Item
{
    public:
    Stock(std::string name="", float price=0.0): Item(name, price) {};

    std::string getName() override {return name;};
    float getPrice() override {return price;};
};