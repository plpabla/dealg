#include <gtest/gtest.h>
#include "../ListWindow.h"
#include "../Stock.h"
#include "../Exceptions.h"

using namespace std;

TEST(ListWindowTest, GettingCurrentItemFromEmptyListReturnsNull)
{
    ListWindow<Stock> lw;

    Stock* item;
    item = lw.getCurrentItem();

    ASSERT_EQ(item, nullptr);
}

TEST(ListWindowTest, CanCreateListOfObjects)
{
    ListWindow<Stock> lw;
    Stock s1 = Stock("Wheat");
    lw.add(s1);
    Stock* current = lw.getCurrentItem();

    ASSERT_FALSE(current == nullptr);
    ASSERT_TRUE(s1.getName()==current->getName());
}

TEST(ListWindowTest, LastCreatedIsCurrentlySelected)
{
    ListWindow<Stock> lw;
    Stock s1 = Stock("Item A");
    Stock s2 = Stock("Item B");
    
    lw.add(s1);
    lw.add(s2);
    Stock* current = lw.getCurrentItem();

    ASSERT_FALSE(current == nullptr);
    ASSERT_TRUE(s2.getName()==current->getName()) 
        << "Current: " << current->getName() << ", last added: " << s2.getName();
}