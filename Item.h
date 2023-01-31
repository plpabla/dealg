#include <string>

class Item
{
    protected:
    std::string name;
    float price;
    float price_min, price_max;
    
    public:
    Item(std::string name="", float price=0.0): 
        name(name), price(price), price_min(price), price_max(price) {};

    std::string getName() {return name;};
    float getPrice() {return price;};
    void setPriceRange(float pmin, float pmax);
};