#include <gtest/gtest.h>
#include <string>
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