#include <gtest/gtest.h>
#include "test_helpers.h"
#include "../Baner.h"

/************************
 * Baner init
*************************/
TEST(BanerTest, InitializedDefaultFrameHasCorrectSize) { 
    Baner b0;
    ASSERT_EQ(b0.GetWidth(), SCREEN_WIDTH);
    ASSERT_EQ(b0.GetHeight(), SCREEN_HEIGHT);
}


/************************
 * Baner display
*************************/
TEST(BanerTest, BanerDisplaysText) { 
    Baner b0(20, 3, 'x', "Hello", '.');
    Canvas c;
    b0.draw(c, 2, 1);

    CompareStringParts("                           ", c, 0, 0);
    CompareStringParts("  xxxxxxxxxxxxxxxxxxxx     ", c, 0, 1);
    CompareStringParts("  x.Hello............x     ", c, 0, 2);
    CompareStringParts("  xxxxxxxxxxxxxxxxxxxx     ", c, 0, 3);
    CompareStringParts("                           ", c, 0, 4);
}