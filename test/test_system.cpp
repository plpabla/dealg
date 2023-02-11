#include <gtest/gtest.h>
#include <string>
#include "test_helpers.h"

#include "../parameters.h"
#include "../System.h"
#include "../Canvas.h"
#include "../Baner.h"

using namespace std;

TEST(SystemTest, CreatedSystemHasCanvasObjectWithGivenSize)
{
    System s;

    Canvas* pc = s.getCanvas();

    ASSERT_EQ(sizeof(pc->canvas)/sizeof(string), SCREEN_HEIGHT);
}


TEST(SystemTest, CanCreateCanvasWithCustomizedFilling)
{
    System s('.');

    Canvas* pc = s.getCanvas();

    ASSERT_EQ(pc->canvas[0][0], '.');
}

/******************
 * Add window 
 ******************/
TEST(SystemTest, CanAddWindow)
{
    System s;
    Baner b0;
    ASSERT_EQ(s.getWindowsCount(), 0);

    s.addWindow(&b0);

    ASSERT_EQ(s.getWindowsCount(), 1);
}

/******************
 * Remove window 
 ******************/
TEST(SystemTest, CanRemoveLastWindow)
{
    System s;
    Baner b0;
    s.addWindow(&b0);
    ASSERT_EQ(s.getWindowsCount(), 1);

    s.removeLastWindow();
    ASSERT_EQ(s.getWindowsCount(), 0);
}

/******************
 * Drawing 
 ******************/
TEST(SystemTest, DrawAllWindows)
{
    System s('.');
    Baner b0("Hello",'x');
    Baner b1("Hi",'@');
    s.addWindow(&b0,2,1);
    s.addWindow(&b1,10,2);

    s.draw();

    Canvas *pc = s.getCanvas();
    CompareStringParts(".....................", *pc, 0, 0);
    CompareStringParts("..xxxxxxxxx..........", *pc, 0, 1);
    CompareStringParts("..x Hello @@@@@@.....", *pc, 0, 2);
    CompareStringParts("..xxxxxxxx@ Hi @.....", *pc, 0, 3);
    CompareStringParts("..........@@@@@@.....", *pc, 0, 4);
    CompareStringParts(".....................", *pc, 0, 5);
}