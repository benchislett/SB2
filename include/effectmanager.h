#pragma once

#include "effect.h"
#include "trigger.h"

#include <array>
#include <memory>
#include <queue>
#include <vector>

struct Character;
struct Player;

struct EffectManager {
  std::array<std::vector<std::shared_ptr<Trigger>>, NUM_TRIGGERS> triggers;
  std::queue<std::shared_ptr<Effect>> effects;

  std::vector<std::shared_ptr<TriggerState>> history;

  // Add a listener trigger
  void registerTrigger(std::shared_ptr<Trigger>);

  // Activate an event
  void on(std::shared_ptr<TriggerState>);

  // Push an effect
  void push(std::shared_ptr<Effect>);

  // Resolve the effects queue
  void resolveEffects();

  // Cleanup any intermediate state
  void reset();
};
