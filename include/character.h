#pragma once

struct Character {
  int attack, base_attack;
  int health, base_health;

  Character(int atk, int hp) : attack(atk), base_attack(atk), health(hp), base_health(hp) {}

  int getAttack() const;
  int getHealth() const;

  bool takeDamage(int dmg);
  bool hasDied() const;
};
