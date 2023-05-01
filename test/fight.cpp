#include "fight.h"

#include "character.h"

#include <gtest/gtest.h>

TEST(BattleTests, Bounce) {
  Character attacker(4, 5);
  Character defender(3, 6);

  battle(attacker, defender);

  ASSERT_FALSE(attacker.hasDied());
  ASSERT_FALSE(defender.hasDied());
}

TEST(BattleTests, AttackerDies) {
  Character attacker(4, 2);
  Character defender(3, 6);

  battle(attacker, defender);

  ASSERT_TRUE(attacker.hasDied());
  ASSERT_FALSE(defender.hasDied());
}

TEST(BattleTests, DefenderDies) {
  Character attacker(4, 4);
  Character defender(3, 1);

  battle(attacker, defender);

  ASSERT_FALSE(attacker.hasDied());
  ASSERT_TRUE(defender.hasDied());
}

TEST(BattleTests, BothDie) {
  Character attacker(4, 4);
  Character defender(4, 4);

  battle(attacker, defender);

  ASSERT_TRUE(attacker.hasDied());
  ASSERT_TRUE(defender.hasDied());
}