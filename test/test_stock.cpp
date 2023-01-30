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