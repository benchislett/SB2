#pragma once

#include "character.h"
#include "effectmanager.h"
#include "player.h"

#include <array>
#include <memory>

enum FightStepRecordType {
  FIGHT_STEP_ATTACKS,
  FIGHT_STEP_ATTACK_DAMAGE,
};

enum FightResult { FIGHT_ONGOING, FIGHT_DRAW, FIGHT_WINNER1, FIGHT_WINNER2 };
struct FightState {
  EffectManager manager;
  std::shared_ptr<Player> p1;
  std::shared_ptr<Player> p2;
  bool turn; // true if player 1 is the next to attack

  bool initialized = false;

  FightState(std::shared_ptr<Player>, std::shared_ptr<Player>);

  // start the fight and handle triggers
  void init();

  // compute a single attack, plus triggers
  // deals damage but does not reset the board
  void step();

  // resets the player's boards, handling permanent buffs appropriately
  void cleanup();

  // check if the fight has ended, and if so which player has won
  FightResult result() const;
};

// helper to run an entire fight, reset the board, and deal damage
FightResult computeFullFight(std::shared_ptr<Player>, std::shared_ptr<Player>);
