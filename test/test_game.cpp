#include <gtest/gtest.h>
#include "test_helpers.h"
#include "../Game.h"

using namespace std;

TEST(GameTest, CanInitWithDefaults)
{
    ASSERT_NO_THROW(Game g);
}