#include "character.h"

#include <gtest/gtest.h>

TEST(CharacterTests, Initialization) {
  Character test(4, 5);
  ASSERT_EQ(test.getAttack(), 4);
  ASSERT_EQ(test.getHealth(), 5);
}


TEST(CharacterTests, DeathState) {
  Character test_alive(4, 1);

  ASSERT_FALSE(test_alive.dead());

  Character test_dead(4, 0);

  ASSERT_TRUE(test_dead.dead());
}


TEST(CharacterTests, ChipDamage) {
  Character test(4, 5);

  ASSERT_FALSE(test.dead());

  test.takeDamage(1);
  ASSERT_FALSE(test.dead());

  test.takeDamage(1);
  ASSERT_FALSE(test.dead());

  test.takeDamage(1);
  ASSERT_FALSE(test.dead());

  test.takeDamage(1);
  ASSERT_FALSE(test.dead());

  test.takeDamage(1);
  ASSERT_TRUE(test.dead());
}

TEST(CharacterTests, ExactDamage) {
  Character test(0, 6);

  ASSERT_FALSE(test.dead());

  test.takeDamage(6);
  ASSERT_TRUE(test.dead());
}
