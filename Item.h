#include <string>

class Item
{
    protected:
    std::string name;
    float price;
    
    public:
    Item(std::string name="", float price=0.0): name(name), price(price) {};

    std::string getName() {return name;};
    float getPrice() {return price;};
};