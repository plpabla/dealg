#include <gtest/gtest.h>
#include "test_helpers.h"
#include "../Canvas.h"
#include "../Frame.h"
#include "../parameters.h"

using namespace std;

/************************
 * Frame init
*************************/
TEST(FrameTest, InitializedDefaultFrameHasCorrectSize) { 
    Frame f0;
    ASSERT_EQ(f0.GetWidth(), SCREEN_WIDTH);
    ASSERT_EQ(f0.GetHeight(), SCREEN_HEIGHT);
}

TEST(FrameTest, InitializedParamFrameReturnsNewDim) { 
    Frame f0(100, 20);
    ASSERT_EQ(f0.GetWidth(), 100);
    ASSERT_EQ(f0.GetHeight(), 20);
}

/************************
 * Frame 1x1
*************************/
TEST(FrameTest, DrawOneDefaultPointOnBeginningOfCanvas)
{
    Frame f0(1, 1);
    Canvas c;
    f0.draw(c, 0, 0);
    ASSERT_EQ(c.canvas[0][0], 'X') << "Frame drawn here";
    ASSERT_EQ(c.canvas[0][1], ' ') << "Empty here";
    ASSERT_EQ(c.canvas[1][0], ' ') << "Empty here";
    ASSERT_EQ(c.canvas[1][1], ' ') << "Empty here";
}

TEST(FrameTest, DrawOnePointOnBeginningOfCanvas)
{
    Frame f0(1, 1, '.');
    Canvas c;
    f0.draw(c, 0, 0);
    ASSERT_EQ(c.canvas[0][0], '.') << "Frame drawn here";
    ASSERT_EQ(c.canvas[0][1], ' ') << "Empty here";
    ASSERT_EQ(c.canvas[1][0], ' ') << "Empty here";
    ASSERT_EQ(c.canvas[1][1], ' ') << "Empty here";
}

TEST(FrameTest, DrawOnePointShifted)
{
    Frame f0(1, 1);
    Canvas c;
    f0.draw(c, SCREEN_WIDTH-1, SCREEN_HEIGHT-1);
    ASSERT_EQ(c.canvas[SCREEN_HEIGHT-1][SCREEN_WIDTH-1], 'X') << "Frame drawn here";
}

TEST(FrameTest, DrawOnePointOutsideBoundShouldDoNothing)
{
    Frame f0(1, 1);
    Canvas c;
    f0.draw(c, SCREEN_WIDTH, SCREEN_HEIGHT);
}

/************************
 * Frame M x 1
*************************/
TEST(FrameTest, FrameMx1IsCreatedCorrectly)
{
    Frame f0(4, 1, 'x');
    Canvas c('.');
    f0.draw(c, 0, 0);
    CompareStringParts("xxxx.", c, 0, 0);
}

TEST(FrameTest, FrameMx1IsCreatedCorrectlyInAnotherPlace)
{
    Frame f0(4, 1, 'x');
    Canvas c('.');
    f0.draw(c, 2, 1);
    CompareStringParts("..xxxx.", c, 0, 1, "should be a line");
}

TEST(FrameTest, FrameMx1outOfBoundIsCropped)
{
    Frame f0(40, 1, 'x');
    Canvas c('.');

    ASSERT_NO_THROW(f0.draw(c, SCREEN_WIDTH-2, 0));

    CompareStringParts(".xx", c, SCREEN_WIDTH-3, 0);
    ASSERT_EQ(c.canvas[0].length(), SCREEN_WIDTH) << "string has different length";
}

/************************
 * Frame 1 x N
*************************/
TEST(FrameTest, Frame1xNIsCreatedCorrectly)
{
    constexpr int HEIGHT = 4;
    Frame f0(1, HEIGHT, 'x');
    Canvas c('.');
    f0.draw(c, 0, 0);
    for(int row=0; row<HEIGHT; row++)
    {
        ostringstream msg;
        msg << "Error for row " << row;
        CompareStringParts("x.", c, 0, row, msg.str());
    }
    CompareStringParts("..", c, 0, HEIGHT);
}

TEST(FrameTest, Frame1xNIsCreatedCorrectlyInDiffPlace)
{
    constexpr int HEIGHT = 4;
    constexpr int X_0 = 3;
    constexpr int Y_0 = 6;
    Frame f0(1, HEIGHT, 'x');
    Canvas c('.');
    f0.draw(c, X_0, Y_0);
    for(int row=Y_0; row<(Y_0+HEIGHT); row++)
    {
        ostringstream msg;
        msg << "Error for row " << row;
        CompareStringParts(".x.", c, X_0-1, row, msg.str());
    }
    CompareStringParts("...", c, X_0-1, Y_0+HEIGHT);
}

TEST(FrameTest, Frame1xNCreatedOutOfBoundDoesntGenereateError)
{
    constexpr int HEIGHT = 40;
    constexpr int X_0 = 3;
    constexpr int Y_0 = SCREEN_HEIGHT-2;
    Frame f0(1, HEIGHT, 'x');
    Canvas c('.');
    
    ASSERT_NO_THROW(f0.draw(c, X_0, Y_0));

    for(int row=Y_0; row<SCREEN_HEIGHT; row++)
    {
        CompareStringParts(".x.", c, X_0-1, row);
    }
}

/************************
 * Frame M x N
*************************/
TEST(FrameTest, FrameMxNCreated)
{
    constexpr int X_0 = 0;
    constexpr int Y_0 = 0;
    Frame f0(3, 2, 'x');
    Canvas c('.');
    
    ASSERT_NO_THROW(f0.draw(c, X_0, Y_0));

    CompareStringParts("xxx..", c, X_0, 0);
    CompareStringParts("xxx..", c, X_0, 1);
    CompareStringParts(".....", c, X_0, 2);
}

TEST(FrameTest, FrameMxNEmptyInside)
{
    constexpr int X_0 = 0;
    constexpr int Y_0 = 0;
    Frame f0(4, 3, 'x');
    Canvas c('.');
    
    ASSERT_NO_THROW(f0.draw(c, X_0, Y_0));

    CompareStringParts("xxxx..", c, X_0, 0);
    CompareStringParts("x  x..", c, X_0, 1);
    CompareStringParts("xxxx..", c, X_0, 2);
    CompareStringParts("......", c, X_0, 3);
}

TEST(FrameTest, FrameMxNOnBorder)
{
    constexpr int X_0 = SCREEN_WIDTH-5;
    constexpr int Y_0 = SCREEN_HEIGHT-4;
    Frame f0(5, 4, 'x');
    Canvas c('.');
    
    ASSERT_NO_THROW(f0.draw(c, X_0, Y_0));

    CompareStringParts("......", c, X_0-1, SCREEN_HEIGHT-5);
    CompareStringParts(".xxxxx", c, X_0-1, SCREEN_HEIGHT-4);
    CompareStringParts(".x   x", c, X_0-1, SCREEN_HEIGHT-3);
    CompareStringParts(".x   x", c, X_0-1, SCREEN_HEIGHT-2);
    CompareStringParts(".xxxxx", c, X_0-1, SCREEN_HEIGHT-1);
}

TEST(FrameTest, FrameMxNOnBorderPlus1)
{
    constexpr int X_0 = SCREEN_WIDTH-4;
    constexpr int Y_0 = SCREEN_HEIGHT-3;
    Frame f0(5, 4, 'x');
    Canvas c('.');
    
    ASSERT_NO_THROW(f0.draw(c, X_0, Y_0));

    CompareStringParts(".....", c, X_0-1, SCREEN_HEIGHT-4,"top");
    CompareStringParts(".xxxx", c, X_0-1, SCREEN_HEIGHT-3);
    CompareStringParts(".x   ", c, X_0-1, SCREEN_HEIGHT-2);
    CompareStringParts(".x   ", c, X_0-1, SCREEN_HEIGHT-1,"bottom");
}

TEST(FrameTest, FrameMxNOnBorderOnlyCorner)
{
    constexpr int X_0 = SCREEN_WIDTH-1;
    constexpr int Y_0 = SCREEN_HEIGHT-1;
    Frame f0(5, 4, 'x');
    Canvas c('.');
    
    ASSERT_NO_THROW(f0.draw(c, X_0, Y_0));

    CompareStringParts(".x", c, X_0-1, SCREEN_HEIGHT-1,"bottom");
}