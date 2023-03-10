#pragma once
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
    virtual ~Item() {};

    std::string getName() const {return name;};
    float getPrice() const {return price;};
    void setPriceRange(float pmin, float pmax);
    virtual void updatePrice(void);
    virtual void randomizePriceRange(float max_percent=0.0);
};