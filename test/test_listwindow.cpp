#include <gtest/gtest.h>
#include <ncurses.h>
#include "test_helpers.h"
#include "../ListWindow.h"
#include "../Stock.h"
#include "../Canvas.h"
#include "../parameters.h"

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

/***********************
 * Drawing
 **********************/
TEST(ListWindowTest, CanInitializeAsFrame)
{
    ListWindow<Stock> lw(SCREEN_WIDTH, SCREEN_HEIGHT, 'x', '.');
}

TEST(ListWindowTest, EmptyListIsDrawnAsEmptyFrame)
{
    ListWindow<Stock> lw(6, 4, 'x', '.');
    Canvas c(' ');
    lw.draw(c, 2, 1);
    CompareStringParts("          ", c, 0, 0);
    CompareStringParts("  xxxxxx  ", c, 0, 1);
    CompareStringParts("  x....x  ", c, 0, 2);
    CompareStringParts("  x....x  ", c, 0, 3);
    CompareStringParts("  xxxxxx  ", c, 0, 4);
    CompareStringParts("          ", c, 0, 5);
}

TEST(ListWindowTest, ListWithOneItemDrawnCorrectly)
{
    ListWindow<Stock> lw(20, 4, 'x', '.');
    lw.add(Stock("Item1"));
    Canvas c(' ');
    lw.draw(c, 2, 1);
    CompareStringParts("                        ", c, 0, 0);
    CompareStringParts("  xxxxxxxxxxxxxxxxxxxx  ", c, 0, 1);
    CompareStringParts("  x> Item1......0.00 x  ", c, 0, 2);
    CompareStringParts("  x..................x  ", c, 0, 3);
    CompareStringParts("  xxxxxxxxxxxxxxxxxxxx  ", c, 0, 4);
    CompareStringParts("                        ", c, 0, 5);
}

TEST(ListWindowTest, WhenItemIsTooLongItIsCut)
{
    ListWindow<Stock> lw(10, 4, 'x', '.');
    lw.add(Stock("LongerItemName"));
    Canvas c(' ');
    lw.draw(c, 2, 1);
    CompareStringParts("              ", c, 0, 0);
    CompareStringParts("  xxxxxxxxxx  ", c, 0, 1);
    CompareStringParts("  x> L0.00 x  ", c, 0, 2);
    CompareStringParts("  x........x  ", c, 0, 3);
    CompareStringParts("  xxxxxxxxxx  ", c, 0, 4);
    CompareStringParts("              ", c, 0, 5);
}

TEST(ListWindowTest, ListWithTwoItemsDrawnCorrectly)
{
    ListWindow<Stock> lw(20, 4, 'x', '.');
    lw.add(Stock("Item1"));
    lw.add(Stock("Item B"));
    Canvas c(' ');
    lw.draw(c, 2, 1);
    CompareStringParts("                        ", c, 0, 0);
    CompareStringParts("  xxxxxxxxxxxxxxxxxxxx  ", c, 0, 1);
    CompareStringParts("  x> Item1......0.00 x  ", c, 0, 2);
    CompareStringParts("  x  Item B.....0.00 x  ", c, 0, 3);
    CompareStringParts("  xxxxxxxxxxxxxxxxxxxx  ", c, 0, 4);
    CompareStringParts("                        ", c, 0, 5);
}

TEST(ListWindowTest, ForMoreItemsThanSizeCroppedListIsDrawn)
{
    ListWindow<Stock> lw(20, 4, 'x', '.');
    lw.add(Stock("Item1"));
    lw.add(Stock("Item B"));
    lw.add(Stock("Should be not displayed"));
    Canvas c(' ');
    lw.draw(c, 2, 1);
    CompareStringParts("                        ", c, 0, 0);
    CompareStringParts("  xxxxxxxxxxxxxxxxxxxx  ", c, 0, 1);
    CompareStringParts("  x> Item1......0.00 x  ", c, 0, 2);
    CompareStringParts("  x  Item B.....0.00 x  ", c, 0, 3);
    CompareStringParts("  xxxxxxxxxxxxxxxxxxxx  ", c, 0, 4);
    CompareStringParts("                        ", c, 0, 5);
}

TEST(ListWindowTest, CursorOnPositionDifferntThanOneIsDisplayedCorrectly)
{
    ListWindow<Stock> lw(20, 4, 'x', '.');
    lw.add(Stock("Item1"));
    lw.add(Stock("Item B"));
    lw.navigate(KEY_DOWN);
    Canvas c(' ');
    lw.draw(c, 2, 1);
    CompareStringParts("                        ", c, 0, 0);
    CompareStringParts("  xxxxxxxxxxxxxxxxxxxx  ", c, 0, 1);
    CompareStringParts("  x  Item1......0.00 x  ", c, 0, 2);
    CompareStringParts("  x> Item B.....0.00 x  ", c, 0, 3);
    CompareStringParts("  xxxxxxxxxxxxxxxxxxxx  ", c, 0, 4);
    CompareStringParts("                        ", c, 0, 5);
}

TEST(ListWindowTest, CannotNavigateOver)
{
    ListWindow<Stock> lw(20, 4, 'x', '.');
    lw.add(Stock("Item1"));
    lw.add(Stock("Item B"));
    lw.navigate(KEY_UP);
    Canvas c(' ');
    lw.draw(c, 2, 1);
    CompareStringParts("                        ", c, 0, 0);
    CompareStringParts("  xxxxxxxxxxxxxxxxxxxx  ", c, 0, 1);
    CompareStringParts("  x> Item1......0.00 x  ", c, 0, 2);
    CompareStringParts("  x  Item B.....0.00 x  ", c, 0, 3);
    CompareStringParts("  xxxxxxxxxxxxxxxxxxxx  ", c, 0, 4);
    CompareStringParts("                        ", c, 0, 5);
}

TEST(ListWindowTest, CannotNavigateUnder)
{
    ListWindow<Stock> lw(20, 4, 'x', '.');
    lw.add(Stock("Item1"));
    lw.add(Stock("Item B"));
    lw.navigate(KEY_DOWN);
    lw.navigate(KEY_DOWN);
    Canvas c(' ');
    lw.draw(c, 2, 1);
    CompareStringParts("                        ", c, 0, 0);
    CompareStringParts("  xxxxxxxxxxxxxxxxxxxx  ", c, 0, 1);
    CompareStringParts("  x  Item1......0.00 x  ", c, 0, 2);
    CompareStringParts("  x> Item B.....0.00 x  ", c, 0, 3);
    CompareStringParts("  xxxxxxxxxxxxxxxxxxxx  ", c, 0, 4);
    CompareStringParts("                        ", c, 0, 5);
}

TEST(ListWindowTest, DisplayAlsoPrices)
{
    ListWindow<Stock> lw(24, 4, 'x', '.');
    lw.add(Stock("Item1", 20.401, 100));
    lw.add(Stock("Item B", 145.00, 600));
    Canvas c(' ');
    lw.draw(c, 2, 1);
    CompareStringParts("                            ", c, 0, 0);
    CompareStringParts("  xxxxxxxxxxxxxxxxxxxxxxxx  ", c, 0, 1);
    CompareStringParts("  x> Item1.........20.40 x  ", c, 0, 2);
    CompareStringParts("  x  Item B.......145.00 x  ", c, 0, 3);
    CompareStringParts("  xxxxxxxxxxxxxxxxxxxxxxxx  ", c, 0, 4);
    CompareStringParts("                            ", c, 0, 5);
}

TEST(ListWindowTest, DisplayQty)
{
    ListWindow<Stock> lw(30, 4, 'x', '.', 4);
    lw.add(Stock("Item1", 20.401, 100));
    lw.add(Stock("Item B", 145.00, 60));
    Canvas c(' ');
    lw.draw(c, 2, 1);
    CompareStringParts("                                  ", c, 0, 0);
    CompareStringParts("  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  ", c, 0, 1);
    CompareStringParts("  x> Item1.........20.40 x 100 x  ", c, 0, 2);
    CompareStringParts("  x  Item B.......145.00 x  60 x  ", c, 0, 3);
    CompareStringParts("  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  ", c, 0, 4);
    CompareStringParts("                                  ", c, 0, 5);
}

TEST(ListWindowTest, DisplayShortQty)
{
    ListWindow<Stock> lw(30, 4, 'x', '.', 2);
    lw.add(Stock("Item1", 20.401, 10));
    lw.add(Stock("Item B", 145.00, 60));
    Canvas c(' ');
    lw.draw(c, 2, 1);
    CompareStringParts("                                  ", c, 0, 0);
    CompareStringParts("  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  ", c, 0, 1);
    CompareStringParts("  x> Item1...........20.40 x10 x  ", c, 0, 2);
    CompareStringParts("  x  Item B.........145.00 x60 x  ", c, 0, 3);
    CompareStringParts("  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  ", c, 0, 4);
    CompareStringParts("                                  ", c, 0, 5);
}

TEST(ListWindowTest, LongerQtyIsCut)
{
    ListWindow<Stock> lw(30, 4, 'x', '.', 2);
    lw.add(Stock("Item1", 20.401, 100));
    lw.add(Stock("Item B", 145.00, 99));
    Canvas c(' ');
    lw.draw(c, 2, 1);
    CompareStringParts("                                  ", c, 0, 0);
    CompareStringParts("  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  ", c, 0, 1);
    CompareStringParts("  x> Item1...........20.40 x?? x  ", c, 0, 2);
    CompareStringParts("  x  Item B.........145.00 x99 x  ", c, 0, 3);
    CompareStringParts("  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  ", c, 0, 4);
    CompareStringParts("                                  ", c, 0, 5);
}

/***********************
 * Update prices
 **********************/
TEST(ListWindowTest, CanUpdteAllPrices)
{
    ListWindow<Stock> lw(30, 4, 'x', '.', 2);
    lw.add(Stock("Item 1", 10.0, 0, 42.0, 42.0));
    lw.add(Stock("Item B", 11.0, 0, 69.0, 69.0));
    // Check initial prices
    ASSERT_EQ(lw.getCurrentItem()->getPrice(), 10.0);
    lw.navigate(KEY_DOWN);
    ASSERT_EQ(lw.getCurrentItem()->getPrice(), 11.0);
    lw.navigate(KEY_UP);

    lw.updatePrices();

    ASSERT_EQ(lw.getCurrentItem()->getPrice(), 42.0);
    lw.navigate(KEY_DOWN);
    ASSERT_EQ(lw.getCurrentItem()->getPrice(), 69.0);
    lw.navigate(KEY_UP);
}