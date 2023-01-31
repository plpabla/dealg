#include <string>
#include "Item.h"

class Stock: public Item
{
    protected:
    int quantity;
    public:
    Stock(std::string name="", float price=0.0, int qty=0): Item(name, price), quantity(qty) {};

    std::string getName() override {return name;};
    float getPrice() override {return price;};
    int getQty() {return quantity;};
};