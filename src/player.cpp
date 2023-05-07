// import stdio;
#include "player.h"

#include "rng.h"

#include <algorithm>
#include <cassert>

bool Player::alive() const {
  return health > 0;
}

bool Player::dead() const {
  return !alive();
}

void Player::takeDamage(int amount) {
  health = std::max(health - amount, 0);
}

void Player::addCharacter(std::shared_ptr<Character> character) {
  assert(characters[character->position] == nullptr);
  characters[character->position] = character;
}

std::shared_ptr<Character> Player::nextCharacter(const CharacterFilter& filter) const {
  for (int i = 0; i < 7; i++) {
    std::shared_ptr<Character> character = characters[((battle_slot - 1) + i) % 7];
    if (character != nullptr && filter(character))
      return character;
  }
  return nullptr;
}

std::shared_ptr<Character> Player::nextCharacter() const {
  return nextCharacter([](auto) { return true; });
}

std::shared_ptr<Character> Player::randomCharacter(const CharacterFilter& filter) const {
  std::array<int, 7> refs;
  int matches = 0;
  for (int i = 0; i < 7; i++) {
    std::shared_ptr<Character> character = characters[i];
    if (character != nullptr && filter(character))
      refs[matches++] = i;
  }

  if (matches == 0)
    return nullptr;

  return characters[refs[rand_in_range(0, matches - 1)]];
}

std::shared_ptr<Character> Player::randomCharacter() const {
  return randomCharacter([](auto) { return true; });
}

std::shared_ptr<Character> Player::getDefender(bool flying) const {
  std::shared_ptr<Character> choice = nullptr;

  choice = randomCharacter([flying](auto ch) { return flying ? (ch->position > 4) : (ch->position < 5); });

  if (choice == nullptr)
    choice = randomCharacter();

  return choice;
}

void Player::kill(int position) {
  assert(characters[position]->dead());

  characters[position] = nullptr;
}