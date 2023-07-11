#pragma once

#include <memory>

struct Player;
struct PlayerEffectManager;
struct FightEffectManager;

struct Character {
  int attack;
  int base_health, damage;

  int position;

  Character(int atk = 0, int hp = 1, int pos = 1) : attack(atk), base_health(hp), damage(0), position(pos) {}

  // register effects on the player scope
  virtual void playerInit(PlayerEffectManager& m) {}

  // register effects on this fight scope
  virtual void fightInit(FightEffectManager& m) {}

  virtual ~Character() {}

  int getAttack() const;
  int getHealth() const; // active health, minus damage taken
  int getBaseHealth() const;
  void setAttack(int);
  void setHealth(int);

  void takeDamage(int);

  bool golden() const;
  bool dead() const;
  bool alive() const;
};
