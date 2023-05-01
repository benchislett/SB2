#include "character.h"

#include <gtest/gtest.h>

TEST(CharacterTests, BasicSetup) {
  Character test(4, 5);
  ASSERT_EQ(test.getAttack(), 4);
  ASSERT_EQ(test.getHealth(), 5);
}
