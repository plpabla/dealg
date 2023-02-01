#include <gtest/gtest.h>
#include "../ListWindow.h"
#include "../Stock.h"
#include "../Exceptions.h"

using namespace std;

TEST(ListWindowTest, GettingCurrentItemFromEmptyListThrowsError)
{
    ListWindow<Stock> lw;

    Stock item;
    ASSERT_THROW(item = lw.getCurrentItem(), EmptyListException);
}

TEST(ListWindowTest, CanCreateListOfObjects)
{
    ListWindow<Stock> lw;
    Stock s1 = Stock("Wheat");
    lw.add(s1);
    Stock current = lw.getCurrentItem();

    ASSERT_TRUE(s1==current);
}
