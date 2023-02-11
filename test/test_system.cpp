#include <gtest/gtest.h>
#include <string>
#include "../parameters.h"
#include "../System.h"
#include "../Canvas.h"

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

