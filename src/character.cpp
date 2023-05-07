#include "character.h"

#include <algorithm>
#include <cassert>

int Character::getAttack() const {
  return attack;
}

int Character::getHealth() const {
  return health;
}

void Character::takeDamage(int damage) {
  health = std::max(0, health - damage);
}

bool Character::dead() const {
  assert(health >= 0);

  return health == 0;
}

bool Character::alive() const {
  return !dead();
}
