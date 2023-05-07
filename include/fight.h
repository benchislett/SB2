#pragma once

#include "character.h"
#include "player.h"

#include <array>
#include <memory>

enum FightResult { FIGHT_ONGOING, FIGHT_DRAW, FIGHT_WINNER0, FIGHT_WINNER1 };

FightResult fightResult(const Player& p1, const Player& p2);
void fightStep(Player& p1, Player& p2);
FightResult fight(Player& p1, Player& p2);

bool decide_turn(Player& p1, Player& p2);
