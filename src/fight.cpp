#include "fight.h"

#include "character.h"
#include "player.h"
#include "rng.h"

#include <algorithm>
#include <cassert>

constexpr bool debug_log = false;

FightResult FightState::result() const {
  bool has_attackers[2] = {false, false};
  bool has_units[2]     = {false, false};
  for (int i = 0; i < 7; i++) {
    if (p1->characters[i] != nullptr) {
      has_units[0] |= p1->characters[i]->alive();
      has_attackers[0] |= (p1->characters[i]->alive() && p1->characters[i]->getAttack() > 0);
    }
    if (p2->characters[i] != nullptr) {
      has_units[1] |= p2->characters[i]->alive();
      has_attackers[1] |= (p2->characters[i]->alive() && p2->characters[i]->getAttack() > 0);
    }
  }

  if (has_attackers[0] && has_attackers[1])
    return FIGHT_ONGOING;

  if (has_attackers[0] && has_units[1])
    return FIGHT_ONGOING;

  if (has_attackers[1] && has_units[0])
    return FIGHT_ONGOING;

  if (has_units[0] == has_units[1])
    return FIGHT_DRAW;

  if (has_units[0])
    return FIGHT_WINNER1;

  if (has_units[1])
    return FIGHT_WINNER2;

  assert(false);
}

int count_damage(std::shared_ptr<Player> player) {
  int damage = 0;

  for (int i = 0; i < 7; i++) {
    if (player->characters[i] != nullptr) {
      assert(player->characters[i]->alive());
      damage += player->characters[i]->golden() ? 3 : 1;
    }
  }

  return damage;
}

void FightState::step() {
  assert(initialized);

  std::shared_ptr<Player> attacker = p1;
  std::shared_ptr<Player> defender = p2;

  if (!turn) {
    attacker = p2;
    defender = p1;
  }

  std::shared_ptr<Character> attack_char = attacker->nextCharacter();
  if (attack_char == nullptr)
    return;

  attacker->battle_slot = attack_char->position;

  std::shared_ptr<Character> defend_char = defender->getDefender();

  assert(defend_char != nullptr);

  manager.on(std::make_shared<TriggerStates::CharacterAttacks>(attacker, defender, attack_char, defend_char));

  int a1 = attack_char->getAttack();
  int a2 = defend_char->getAttack();

  manager.push(std::make_shared<DamageEffect>(defend_char, a1));
  manager.push(std::make_shared<DamageEffect>(attack_char, a2));
  manager.resolveEffects();

  if (a1 != 0)
    manager.on(std::make_shared<TriggerStates::DamageTaken>(defender, attacker, defend_char, a1));

  if (a2 != 0)
    manager.on(std::make_shared<TriggerStates::DamageTaken>(attacker, defender, attack_char, a2));

  if (attack_char->dead()) {
    attacker->kill(attack_char->position);
    manager.on(std::make_shared<TriggerStates::CharacterKilled>(attacker, defender, attack_char));
  } else {
    manager.on(std::make_shared<TriggerStates::DamageSurvived>(attacker, defender, attack_char));
  }

  if (defend_char->dead()) {
    defender->kill(defend_char->position);
    manager.on(std::make_shared<TriggerStates::CharacterKilled>(defender, attacker, defend_char));
  } else {
    manager.on(std::make_shared<TriggerStates::DamageSurvived>(defender, attacker, defend_char));
  }

  // fight is over, deal damage
  if (result() != FIGHT_ONGOING) {
    if (result() == FIGHT_WINNER1) {
      p2->takeDamage(count_damage(p1));
    } else if (result() == FIGHT_WINNER2) {
      p1->takeDamage(count_damage(p2));
    }
  }
}

bool decide_turn(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2) {
  if (p1->always_first != p2->always_first)
    return p1->always_first;

  return (bool) rand_in_range(0, 1);
}

FightState::FightState(std::shared_ptr<Player> p_1, std::shared_ptr<Player> p_2) : p1(p_1), p2(p_2) {
  turn = decide_turn(p1, p2);
}

void FightState::init() {
  initialized = true;

  if (debug_log) {
    manager.registerTrigger(std::make_shared<LogTriggers::DamageTaken>());
    manager.registerTrigger(std::make_shared<LogTriggers::DamageSurvived>());
    manager.registerTrigger(std::make_shared<LogTriggers::CharacterKilled>());
    manager.registerTrigger(std::make_shared<LogTriggers::CharacterAttacks>());
  }
}

FightResult computeFullFight(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2) {
  FightState state(p1, p2);

  state.init();

  while (state.result() == FIGHT_ONGOING) {
    state.step();
  }

  state.cleanup();

  return state.result();
}

// TODO:
void FightState::cleanup() {
  manager.reset();
  return;
}
