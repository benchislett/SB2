#include "effectmanager.h"

#include "character.h"

void EffectManager::registerTrigger(std::shared_ptr<Trigger> trigger) {
  triggers[trigger->type()].push_back(trigger);
}

void EffectManager::on(std::shared_ptr<TriggerState> state) {
  history.push_back(state);

  for (auto& trigger : triggers[state->type()]) {
    for (auto& effect : trigger->handle(state)) {
      push(effect);
    }
  }

  resolveEffects();
}

void EffectManager::push(std::shared_ptr<Effect> e) {
  effects.push(e);
}

void EffectManager::resolveEffects() {
  while (!effects.empty()) {
    std::shared_ptr<Effect> effect = effects.front();
    effects.pop();

    effect->resolve();
  }
}

void EffectManager::reset() {
  resolveEffects();

  history.clear();
}
