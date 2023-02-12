#include <gtest/gtest.h>
#include "test_helpers.h"
#include "../InputWindow.h"

TEST(InputWindowTest, CanCreate)
{
    ASSERT_NO_THROW(InputWindow iw);
}