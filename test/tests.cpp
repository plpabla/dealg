#include <gtest/gtest.h>
#include <string>
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
    string expected = "xxxx.";
    string received = c.canvas[0].substr(0, 5);
    ASSERT_TRUE(expected == received) << expected << " != " << received;
}

TEST(FrameTest, FrameMx1IsCreatedCorrectlyInAnotherPlace)
{
    Frame f0(4, 1, 'x');
    Canvas c('.');
    f0.draw(c, 2, 2);
    string expected = "..xxxx.";
    string received = c.canvas[2].substr(0, 7);
    ASSERT_TRUE(expected == received) << expected << " != " << received;
}

TEST(FrameTest, FrameMx1outOfBoundIsCropped)
{
    Frame f0(40, 1, 'x');
    Canvas c('.');
    f0.draw(c, SCREEN_WIDTH-2, 0);
    string expected = ".xx";
    string received = c.canvas[0].substr(SCREEN_WIDTH-3, 3); 
    ASSERT_TRUE(expected == received) 
        << expected << " != " << received << endl << "full line: " << c.canvas[0];  
    ASSERT_EQ(c.canvas[0].length(), SCREEN_WIDTH) << "string has different length";
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}