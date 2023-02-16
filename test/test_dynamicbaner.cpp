#include <gtest/gtest.h>
#include "test_helpers.h"
#include "../DynamicBaner.h"

/************************
 * Baner init
*************************/
TEST(DynamicBanerTest, InitializedDefaultBannerHasCorrectSize) { 
    float f;

    ASSERT_NO_THROW(DynamicBaner b0("Amount", 'x', &f));
}


/************************
 * Baner display
*************************/
TEST(DynamicTest, BanerDisplaysText) { 
    float f0 = 42.0;
    DynamicBaner b0("Amount", 'x', &f0);
    Canvas c;
    b0.draw(c, 2, 1);

    CompareStringParts("                       ", c, 0, 0);
    CompareStringParts("  xxxxxxxxxxxxxxxx     ", c, 0, 1);
    CompareStringParts("  x Amount 42.00 x     ", c, 0, 2);
    CompareStringParts("  xxxxxxxxxxxxxxxx     ", c, 0, 3);
    CompareStringParts("                       ", c, 0, 4);
}

TEST(DynamicTest, BanerDisplaysShorterText) { 
    float f0 = 42.0;
    DynamicBaner b0("Amount", 'x', &f0, 10);
    Canvas c;
    b0.draw(c, 2, 1);

    CompareStringParts("                            ", c, 0, 0);
    CompareStringParts("  xxxxxxxxxxxxxxxxxxxxx     ", c, 0, 1);
    CompareStringParts("  x Amount      42.00 x     ", c, 0, 2);
    CompareStringParts("  xxxxxxxxxxxxxxxxxxxxx     ", c, 0, 3);
    CompareStringParts("                            ", c, 0, 4);
}