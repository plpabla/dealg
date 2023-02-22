#include "Item.h"

void Item::setPriceRange(float pmin, float pmax)
{
    price_min = pmin;
    price_max = pmax;
}

float get_rand_in_range(float min_val=0.0, float max_val=1.0)
{
    float range = max_val-min_val;
    return min_val + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(range)));
}

void Item::updatePrice(void)
{
    price = get_rand_in_range(price_min, price_max);
}


#include <iostream>
using namespace std;
void Item::randomizePriceRange(float max_percent)
{
    price_min *= 1+get_rand_in_range(-1,1)*max_percent;
    price_max *= 1+get_rand_in_range(-1,1)*max_percent;

    if(price_min<0) price_min = get_rand_in_range(100,3000);
    if(price_max<0) price_max = get_rand_in_range(100,3000);

    if(price_max<price_min)
    {
        float tmp = price_min;
        price_min = price_max;
        price_max = tmp;
    }
}