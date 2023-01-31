#include "Item.h"

void Item::setPriceRange(float pmin, float pmax)
{
    price_min = pmin;
    price_max = pmax;
}

void Item::updatePrice(void)
{
    float range = price_max-price_min;
    price = price_min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(range)));
}