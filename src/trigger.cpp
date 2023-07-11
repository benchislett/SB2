#include "trigger.h"

#include "character.h"
#include "player.h"

#include <iostream>
#include <memory>
#include <string>

std::string log(std::shared_ptr<Player> owner, std::shared_ptr<Character> ch) {
  return "Player " + owner->id + "'s character in position " + std::to_string(ch->position);
}

std::vector<std::shared_ptr<Effect>> LogTriggers::DamageTaken::handle(std::shared_ptr<TriggerState> st) {
  auto state = std::dynamic_pointer_cast<TriggerStates::DamageTaken>(st);

  std::cout << log(state->owner, state->source) << " takes " << state->damage << " damage\n";

  return {};
}

std::vector<std::shared_ptr<Effect>> LogTriggers::DamageSurvived::handle(std::shared_ptr<TriggerState> st) {
  auto state = std::dynamic_pointer_cast<TriggerStates::DamageSurvived>(st);

  std::cout << log(state->owner, state->source) << " survived damage\n";

  return {};
}

std::vector<std::shared_ptr<Effect>> LogTriggers::CharacterKilled::handle(std::shared_ptr<TriggerState> st) {
  auto state = std::dynamic_pointer_cast<TriggerStates::CharacterKilled>(st);

  std::cout << log(state->owner, state->source) << " was killed\n";

  return {};
}

std::vector<std::shared_ptr<Effect>> LogTriggers::CharacterAttacks::handle(std::shared_ptr<TriggerState> st) {
  auto state = std::dynamic_pointer_cast<TriggerStates::CharacterAttacks>(st);

  std::cout << log(state->attacker, state->attack_char) << " attacks " << log(state->defender, state->defend_char)
            << "\n";

  return {};
}
