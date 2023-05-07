#include "fight.h"

#include "character.h"
#include "player.h"
#include "rng.h"

#include <algorithm>
#include <cassert>

FightResult fightResult(const Player& p1, const Player& p2) {
  bool has_attackers[2] = {false, false};
  bool has_units[2]     = {false, false};
  for (int i = 0; i < 7; i++) {
    if (p1.characters[i] != nullptr) {
      has_units[0] |= p1.characters[i]->alive();
      has_attackers[0] |= (p1.characters[i]->alive() && p1.characters[i]->getAttack() > 0);
    }
    if (p2.characters[i] != nullptr) {
      has_units[1] |= p2.characters[i]->alive();
      has_attackers[1] |= (p2.characters[i]->alive() && p2.characters[i]->getAttack() > 0);
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
    return FIGHT_WINNER0;

  if (has_units[1])
    return FIGHT_WINNER1;

  assert(false);
}

void fightStep(Player& attacker, Player& defender) {
  std::shared_ptr<Character> attack_char = attacker.nextCharacter();
  if (attack_char == nullptr)
    return;

  attacker.battle_slot = attack_char->position;

  std::shared_ptr<Character> defend_char = defender.getDefender();

  assert(defend_char != nullptr);

  int a1 = attack_char->getAttack();
  int a2 = defend_char->getAttack();

  defend_char->takeDamage(a1);
  attack_char->takeDamage(a2);

  if (attack_char->dead())
    attacker.kill(attack_char->position);

  if (defend_char->dead())
    defender.kill(defend_char->position);
}

bool decide_turn(Player& p1, Player& p2) {
  if (p1.always_first != p2.always_first)
    return p2.always_first;

  return (bool) rand_in_range(0, 1);
}

int count_damage(Player& player) {
  int damage = 0;

  for (int i = 0; i < 7; i++) {
    if (player.characters[i] != nullptr) {
      assert(player.characters[i]->alive());
      damage++;
    }
  }

  return damage;
}

FightResult fight(Player& p1, Player& p2) {
  bool turn = decide_turn(p1, p2);

  FightResult res;
  while ((res = fightResult(p1, p2)) == FIGHT_ONGOING) {
    if (turn)
      fightStep(p2, p1);
    else
      fightStep(p1, p2);
    turn = !turn;
  }

  if (res == FIGHT_WINNER0) {
    p2.takeDamage(count_damage(p1));
  }
  if (res == FIGHT_WINNER1) {
    p1.takeDamage(count_damage(p2));
  }

  return res;
}
