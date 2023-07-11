#pragma once

#include <memory>

struct Character;
struct Player;

struct Effect {
  virtual void resolve() = 0;
  virtual ~Effect() {}
};

struct DamageEffect : Effect {
  std::shared_ptr<Character> target;
  int damage_amount;

  DamageEffect(std::shared_ptr<Character> t, int dmg) : target(t), damage_amount(dmg) {}

  virtual void resolve();
};
