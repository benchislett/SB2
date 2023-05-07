#pragma once

struct Character {
  int attack, base_attack;
  int health, base_health;
  int position;

  Character(int atk, int hp, int pos = 1) : attack(atk), base_attack(atk), health(hp), base_health(hp), position(pos) {}

  int getAttack() const;
  int getHealth() const;
  bool isUpgraded() const;

  void takeDamage(int dmg);
  bool dead() const;
  bool alive() const;
};
