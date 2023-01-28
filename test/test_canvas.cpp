#include <gtest/gtest.h>
#include <string>
#include "../Canvas.h"
#include "../parameters.h"

namespace {

using namespace std;
/************************
 * Canvas
*************************/
TEST(CanvasTest, ContainsCorrectNumberOfLines)
{
    Canvas c;
    ASSERT_EQ(sizeof(c.canvas)/sizeof(string), SCREEN_HEIGHT);
}

TEST(CanvasTest, ContainsCorrectLinesWidth)
{
    Canvas c;
    ASSERT_EQ(c.canvas[0].length(), SCREEN_WIDTH) << "first line";
    ASSERT_EQ(c.canvas[SCREEN_HEIGHT-1].length(), SCREEN_WIDTH) << "last line";
}

TEST(CanvasTest, FilledWithSpaceByDefault)
{
    Canvas c;
    ASSERT_EQ(c.canvas[0][0], ' ');
}

TEST(CanvasTest, FilledWithX)
{
    Canvas c('X');
    ASSERT_EQ(c.canvas[0][0], 'X');
}

}