#include <gtest/gtest.h>
#include "test_helpers.h"
#include "../Baner.h"

/************************
 * Baner init
*************************/
TEST(BanerTest, InitializedDefaultBannerHasCorrectSize) { 
    constexpr int EMTPY_BANNER_WIDTH = 4;
    constexpr int EMTPY_BANNER_HEIGHT = 3;

    Baner b0;
    
    ASSERT_EQ(b0.GetWidth(), EMTPY_BANNER_WIDTH); 
    ASSERT_EQ(b0.GetHeight(), EMTPY_BANNER_HEIGHT);
}


/************************
 * Baner display
*************************/
TEST(BanerTest, BanerDisplaysText) { 
    Baner b0("Hello", 'x');
    Canvas c;
    b0.draw(c, 2, 1);

    CompareStringParts("                ", c, 0, 0);
    CompareStringParts("  xxxxxxxxx     ", c, 0, 1);
    CompareStringParts("  x Hello x     ", c, 0, 2);
    CompareStringParts("  xxxxxxxxx     ", c, 0, 3);
    CompareStringParts("                ", c, 0, 4);
}