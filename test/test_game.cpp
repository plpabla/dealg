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

class TestGame: public Game
{
    public:
    ListWindow<Stock>* create_assets_list(void) {return Game::create_assets_list();};
};

TEST(GameTest, CanAccessAssetsListUsingChildClass)
{
    TestGame g;

    ListWindow<Stock>*p = g.create_assets_list();

    ASSERT_NE(p->getNumberOfElements(), 0);
}

TEST(GameTest, CanInitWithCustomFiles)
{
    ASSERT_NO_THROW(Game g(10000, "assets.txt", "cities.txt"));
}