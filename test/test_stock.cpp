#include <gtest/gtest.h>
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