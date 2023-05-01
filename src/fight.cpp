#include "fight.h"

#include "character.h"

void battle(Character& attacker, Character& defender) {
  int a1 = attacker.getAttack();
  int a2 = defender.getAttack();

  defender.takeDamage(a1);
  attacker.takeDamage(a2);
}