#include <gtest/gtest.h>
#include "../ListWindow.h"
#include "../Stock.h"

using namespace std;

TEST(ListWindowTest, CanCreateListOfObjects)
{
    ListWindow lw;
    Stock *s1 = new Stock("Wheat");

    lw.add(s1);
    Stock *current = dynamic_cast<Stock*>(lw.getCurrentItem());

    ASSERT_EQ(s1, current);
    delete s1;
}
