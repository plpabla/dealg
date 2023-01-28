#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include "../Frame.h"
#include "../Canvas.h"
#include "../parameters.h"

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

/************************
 * Canvas helpers
*************************/
void CompareStringParts(string expected, const Canvas c, int col, int row, string extra_msg="")
{
    string part = c.canvas[col].substr(row, expected.length());
    ASSERT_TRUE(expected == part) 
        << expected << " != " << part << endl 
        << "[" << c.canvas[row] << "]" << " (" << extra_msg << ")" << endl;
}

/************************
 * Frame
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
    f0.draw(c, 2, 2);
    CompareStringParts("..xxxx.", c, 2, 0);
}

TEST(FrameTest, FrameMx1outOfBoundIsCropped)
{
    Frame f0(40, 1, 'x');
    Canvas c('.');
    f0.draw(c, SCREEN_WIDTH-2, 0);
    CompareStringParts(".xx", c, 0, SCREEN_WIDTH-3);
    ASSERT_EQ(c.canvas[0].length(), SCREEN_WIDTH) << "string has different length";
}

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


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}