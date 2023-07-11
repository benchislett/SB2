#include "fight.h"

#include "character.h"

#include <gtest/gtest.h>
#include <memory>

class SimpleFight : public ::testing::Test {
  protected:
  void SetUp() override {
    p1 = std::make_shared<Player>(40, "P1");
    p2 = std::make_shared<Player>(40, "P2");
  }

  void TearDown() override {}

  std::shared_ptr<Player> p1;
  std::shared_ptr<Player> p2;
};

TEST_F(SimpleFight, Bounce) {
  p1->addCharacter(std::make_shared<Character>(4, 5));
  p2->addCharacter(std::make_shared<Character>(3, 6));

  FightResult res = computeFullFight(p1, p2);

  ASSERT_TRUE(res == FIGHT_DRAW);
  ASSERT_EQ(p1->health, 40);
  ASSERT_EQ(p2->health, 40);
}

TEST_F(SimpleFight, AttackerDies) {
  p1->always_first = true;
  p1->addCharacter(std::make_shared<Character>(4, 2));
  p2->addCharacter(std::make_shared<Character>(3, 6));

  FightResult res = computeFullFight(p1, p2);

  ASSERT_TRUE(res == FIGHT_WINNER2);
  ASSERT_EQ(p1->health, 39);
  ASSERT_EQ(p2->health, 40);
}

TEST_F(SimpleFight, DefenderDies) {
  p1->always_first = true;
  p1->addCharacter(std::make_shared<Character>(4, 4));
  p2->addCharacter(std::make_shared<Character>(3, 1));

  FightResult res = computeFullFight(p1, p2);

  ASSERT_TRUE(res == FIGHT_WINNER1);
  ASSERT_EQ(p1->health, 40);
  ASSERT_EQ(p2->health, 39);
}

TEST_F(SimpleFight, Player2Wins) {
  p2->always_first = true;

  p1->addCharacter(std::make_shared<Character>(1, 1, 1));

  // front row, expecting one to die
  p2->addCharacter(std::make_shared<Character>(1, 1, 1));
  p2->addCharacter(std::make_shared<Character>(1, 1, 2));
  p2->addCharacter(std::make_shared<Character>(1, 1, 3));
  p2->addCharacter(std::make_shared<Character>(1, 1, 4));

  // back row, should not be attacked from or into
  p2->addCharacter(std::make_shared<Character>(2, 2, 5));
  p2->addCharacter(std::make_shared<Character>(2, 2, 6));
  p2->addCharacter(std::make_shared<Character>(2, 2, 7));

  FightResult res = computeFullFight(p1, p2);

  ASSERT_TRUE(res == FIGHT_WINNER2);
  ASSERT_EQ(p1->health, 40 - 6); // full board minus one front-row unit
  ASSERT_EQ(p2->health, 40);
}

TEST_F(SimpleFight, BothDie) {
  p1->addCharacter(std::make_shared<Character>(4, 4));
  p2->addCharacter(std::make_shared<Character>(4, 4));

  FightResult res = computeFullFight(p1, p2);

  ASSERT_TRUE(res == FIGHT_DRAW);
  ASSERT_EQ(p1->health, 40);
  ASSERT_EQ(p2->health, 40);
}
