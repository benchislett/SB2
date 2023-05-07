#pragma once

#include "character.h"

#include <array>
#include <functional>
#include <memory>

typedef std::function<bool(std::shared_ptr<Character>)> CharacterFilter;

struct Player {
  int health;
  int battle_slot = 1;

  bool always_first = false;

  std::array<std::shared_ptr<Character>, 7> characters;

  Player(int hp = 40) : health(hp) {}

  void takeDamage(int amount);
  bool dead() const;
  bool alive() const;

  void addCharacter(std::shared_ptr<Character>);
  std::shared_ptr<Character> nextCharacter(const CharacterFilter&) const;
  std::shared_ptr<Character> nextCharacter() const;

  std::shared_ptr<Character> randomCharacter(const CharacterFilter&) const;
  std::shared_ptr<Character> randomCharacter() const;

  std::shared_ptr<Character> getDefender(bool flying = false) const;

  void kill(int position);
};
