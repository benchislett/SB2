#include "character.h"

#include <algorithm>
#include <cassert>

int Character::getAttack() const {
  return attack;
}

int Character::getHealth() const {
  return health;
}

bool Character::takeDamage(int damage) {
  health = std::max(0, health - damage);
  return hasDied();
}

bool Character::hasDied() const {
  assert(health >= 0);

  return health == 0;
}
