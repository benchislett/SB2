#include "character.h"

#include <algorithm>
#include <cassert>

void Character::setAttack(int atk) {
  attack = atk;
}

void Character::setHealth(int hp) {
  base_health = hp;
}

int Character::getAttack() const {
  return attack;
}

int Character::getBaseHealth() const {
  return base_health;
}

int Character::getHealth() const {
  return std::max(0, base_health - damage);
}

void Character::takeDamage(int dmg) {
  damage += dmg;
}

bool Character::golden() const {
  return false;
}

bool Character::dead() const {
  return getHealth() == 0;
}

bool Character::alive() const {
  return !dead();
}
