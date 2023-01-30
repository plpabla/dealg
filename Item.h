#include <string>

class Item
{
    protected:
    std::string name;
    float price;
    
    public:
    Item(std::string name="", float price=0.0): name(name), price(price) {};

    virtual std::string getName() {return name;};
    virtual float getPrice() {return price;};
};