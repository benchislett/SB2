#include "effect.h"

#include "character.h"

void DamageEffect::resolve() {
  target->takeDamage(damage_amount);
}