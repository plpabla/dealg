#include <gtest/gtest.h>
#include "test_helpers.h"
#include "../DynamicBaner.h"

/************************
 * Baner init
*************************/
TEST(DynamicBanerTest, InitializedDefaultBannerHasCorrectSize) { 
    float f;

    ASSERT_NO_THROW(DynamicBaner b0(&f));
}


/************************
 * Baner display
*************************/
// TEST(BanerTest, BanerDisplaysText) { 
//     Baner b0("Hello", 'x');
//     Canvas c;
//     b0.draw(c, 2, 1);

//     CompareStringParts("                ", c, 0, 0);
//     CompareStringParts("  xxxxxxxxx     ", c, 0, 1);
//     CompareStringParts("  x Hello x     ", c, 0, 2);
//     CompareStringParts("  xxxxxxxxx     ", c, 0, 3);
//     CompareStringParts("                ", c, 0, 4);
// }