#include <gtest/gtest.h>
#include "../ListWindow.h"
#include "../Stock.h"
#include "../Exceptions.h"

using namespace std;

/***********************
 * Add and get
 **********************/
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

TEST(ListWindowTest, WhenItemAddedCurrentStillPointsTheFirstOne)
{
    const string FIRST_ITEM = string("Item A");
    ListWindow<Stock> lw;
    Stock s1 = Stock(FIRST_ITEM);
    Stock s2 = Stock("Item B");
    
    lw.add(s1);
    lw.add(s2);

    Stock* current = lw.getCurrentItem();
    ASSERT_FALSE(current == nullptr);
    ASSERT_TRUE(current->getName() == FIRST_ITEM) 
        << "Current: " << current->getName() << ", first added: " << FIRST_ITEM;
}

TEST(ListWindowTest, CanAddMoreItems)
{
    constexpr int MAX_ITER = 100;
    ListWindow<Stock> lw;
    for(int cnt=0;cnt<MAX_ITER;cnt++)
    {
        lw.add(Stock("Test"));
    }

    Stock* current = lw.getCurrentItem();
    ASSERT_FALSE(current == nullptr);
    ASSERT_TRUE(current->getName() == "Test");     
    ASSERT_EQ(lw.getNumberOfElements(), MAX_ITER);
}

/***********************
 * Clean
 **********************/
TEST(ListWindowTest, CleanUpEmptyListDoesNothing)
{
    ListWindow<Stock> lw;

    ASSERT_NO_THROW(lw.removeAll());
    
    ASSERT_EQ(lw.getNumberOfElements(), 0);
}

TEST(ListWindowTest, CleanUpOneElementReturnsEmptyList)
{
    ListWindow<Stock> lw;
    lw.add(Stock("Test"));

    ASSERT_NO_THROW(lw.removeAll());
    
    ASSERT_EQ(lw.getNumberOfElements(), 0);
}

TEST(ListWindowTest, CleanUpMoreElementsReturnsEmptyList)
{
    constexpr int MAX_ITER = 100;
    ListWindow<Stock> lw;
    for(int cnt=0;cnt<MAX_ITER;cnt++)
    {
        lw.add(Stock("Test"));
    }

    ASSERT_NO_THROW(lw.removeAll());
    
    ASSERT_EQ(lw.getNumberOfElements(), 0);
}

TEST(ListWindowTest, AfterCleanupCurrentItemIsNull)
{
    ListWindow<Stock> lw;
    lw.add(Stock("Test"));
    ASSERT_NE(lw.getCurrentItem(), nullptr);

    lw.removeAll();
    
    ASSERT_EQ(lw.getCurrentItem(), nullptr);
}

TEST(ListWindowTest, AfterCleanupCurrentItemIsNullThenAfterAddIsNotNull)
{
    ListWindow<Stock> lw;
    lw.add(Stock("Test"));
    ASSERT_NE(lw.getCurrentItem(), nullptr);

    lw.removeAll();
    lw.add(Stock("Test new"));

    ASSERT_NE(lw.getCurrentItem(), nullptr);
    ASSERT_EQ(lw.getCurrentItem()->getName(), "Test new");
}