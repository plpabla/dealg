#include <gtest/gtest.h>
#include "test_helpers.h"
#include "../Game.h"

using namespace std;

TEST(GameTest, CanInitWithDefaults)
{
    Game g;

    ASSERT_EQ(g.getBudget(), 0);
}

TEST(GameTest, CanInitWithBudget)
{
    Game g(10e3);

    ASSERT_EQ(g.getBudget(), 10000);
}

TEST(GameTest, CanUpdateBudget)
{
    Game g;
    g.setBudget(100);

    ASSERT_EQ(g.getBudget(), 100);
}