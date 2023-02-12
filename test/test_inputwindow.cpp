#include <gtest/gtest.h>
#include "test_helpers.h"
#include "../InputWindow.h"

TEST(InputWindowTest, CanCreate)
{
    ASSERT_NO_THROW(InputWindow iw("Enter number:"));
}

TEST(InputWindowTest, DrawsInputWindow)
{
    InputWindow iw("Enter a number:", 'x');
    Canvas c;
    iw.draw(c, 2, 1);

    CompareStringParts("                                ", c, 0, 0);
    CompareStringParts("  xxxxxxxxxxxxxxxxxxxxxxxxx     ", c, 0, 1);
    CompareStringParts("  x Enter a number:       x     ", c, 0, 2);
    CompareStringParts("  xxxxxxxxxxxxxxxxxxxxxxxxx     ", c, 0, 3);
    CompareStringParts("                                ", c, 0, 4);
}