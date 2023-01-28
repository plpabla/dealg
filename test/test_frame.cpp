#include <gtest/gtest.h>
#include <string>
#include "../Frame.h"
#include "../Canvas.h"
#include "../parameters.h"

namespace {
using namespace std;

/************************
 * Canvas helpers
*************************/
void CompareStringParts(string expected, const Canvas c, int col, int row, string extra_msg="")
{
    string part = c.canvas[row].substr(col, expected.length());
    ASSERT_TRUE(expected == part) 
        << expected << " != " << part << endl 
        << "[" << c.canvas[row] << "]" 
        << " (row " <<row << ", " << extra_msg << ")" << endl;
}

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

}