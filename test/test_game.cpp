#include <gtest/gtest.h>
#include "test_helpers.h"
#include "../Game.h"

using namespace std;

class TestGame: public Game
{
    public:
    TestGame(float budget=0.0, std::string assets_filename="", std::string cities_filename=""):
        Game(budget,assets_filename, cities_filename) {};
    ListWindow<Stock>* create_assets_list(void) {return Game::create_assets_list();};

    ListWindow<Stock>* get_assets() {return pAssets;};
};


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


TEST(GameTest, CanAccessAssetsListUsingChildClass)
{
    TestGame g;

    ListWindow<Stock>*p = g.create_assets_list();

    ASSERT_NE(p->getNumberOfElements(), 0);
}

TEST(GameTest, CanInitWithCustomFiles)
{
    ASSERT_NO_THROW(Game g(10000, "", ""));
}

TEST(GameTest, CorrectlyReadsAssetsFromAFile)
{
    TestGame g(100.00, "../test/test_assets.txt", "../test/test_cities.txt");

    ASSERT_NE(g.get_assets(), nullptr);
    ASSERT_EQ(g.get_assets()->getNumberOfElements(), 2);
    ASSERT_EQ(g.get_assets()->getCurrentItem()->getName(), "TestA");
}