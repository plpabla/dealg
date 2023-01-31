#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "../parameters.h"
#include "../Stock.h"

using namespace std;

TEST(StockTest, CanGenerateItemWith012args)
{
    Stock s1();
    Stock s2("Wheat");
    Stock s3("Wheat", 42.0);
}

TEST(StockTest, CanAccessItemNameAndPrice)
{
    Stock s("Wheat", 42.0);
    ASSERT_TRUE(s.getName()=="Wheat");
    ASSERT_FLOAT_EQ(42.0, s.getPrice());
}

TEST(StockTest, CanAccessItemQty)
{
    Stock s("Wheat", 42.0, 100);
    ASSERT_EQ(100, s.getQty());
}

TEST(StockTest, CanDefinePriceRange)
{
    Stock s("Wheat", 42.0);
    s.setPriceRange(100, 200);
}

/**********************
 * updatePrice() 
***********************/
TEST(StockTest, UpdatedPriceIsTheSameIfNoRangeDefined)
{
    constexpr float INITIAL_PRICE = 42.0;
    Stock s("Wheat", INITIAL_PRICE);

    s.updatePrice();

    ASSERT_EQ(INITIAL_PRICE, s.getPrice());
}

TEST(StockTest, UpdatedPriceGeneratesPricesInGivenRange)
{
    constexpr float MIN_PRICE = 100.0;
    constexpr float MAX_PRICE = 200.0;
    constexpr int NO_OF_TESTS = 10;
    std::vector<float> results(NO_OF_TESTS);
    Stock s("Test", MIN_PRICE);
    s.setPriceRange(MIN_PRICE, MAX_PRICE);

    for(int cnt=0; cnt<NO_OF_TESTS; cnt++)
    {
        s.updatePrice();
        results[cnt] = s.getPrice();
    }

    auto it = std::minmax_element(results.begin(), results.end());
    float min = *it.first;
    float max = *it.second;  
    float range = max - min;  

    ASSERT_TRUE(min>=MIN_PRICE);
    ASSERT_TRUE(max<=MAX_PRICE);
    ASSERT_TRUE(range >= (0.9*(MAX_PRICE-MIN_PRICE))) << "Actual range: " << min << "-" << max;
}