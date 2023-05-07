#include "fight.h"

#include "character.h"

#include <gtest/gtest.h>

TEST(Fight1v1, Bounce) {
  Player p1, p2;
  p1.addCharacter(std::make_shared<Character>(4, 5));
  p2.addCharacter(std::make_shared<Character>(3, 6));

  int res = fight(p1, p2);

  ASSERT_TRUE(res == FIGHT_DRAW);
  ASSERT_EQ(p1.health, 40);
  ASSERT_EQ(p2.health, 40);
}

TEST(Fight1v1, AttackerDies) {
  Player p1, p2;
  p1.always_first = true;
  p1.addCharacter(std::make_shared<Character>(4, 2));
  p2.addCharacter(std::make_shared<Character>(3, 6));

  int res = fight(p1, p2);

  ASSERT_TRUE(res == FIGHT_WINNER1);
  ASSERT_EQ(p1.health, 39);
  ASSERT_EQ(p2.health, 40);
}

TEST(Fight1v1, DefenderDies) {
  Player p1, p2;
  p1.always_first = true;
  p1.addCharacter(std::make_shared<Character>(4, 4));
  p2.addCharacter(std::make_shared<Character>(3, 1));

  int res = fight(p1, p2);

  ASSERT_TRUE(res == FIGHT_WINNER0);
  ASSERT_EQ(p1.health, 40);
  ASSERT_EQ(p2.health, 39);
}

TEST(Fight1v1, BothDie) {
  Player p1, p2;
  p1.addCharacter(std::make_shared<Character>(4, 4));
  p2.addCharacter(std::make_shared<Character>(4, 4));

  int res = fight(p1, p2);

  ASSERT_TRUE(res == FIGHT_DRAW);
  ASSERT_EQ(p1.health, 40);
  ASSERT_EQ(p2.health, 40);
}
