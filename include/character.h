#pragma once

struct Character {
  int attack;
  int health;

  Character(int atk, int hp) : attack(atk), health(hp) {}

  int getAttack() const;
  int getHealth() const;
};
