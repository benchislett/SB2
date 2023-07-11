#pragma once

#include "effect.h"

#include <memory>
#include <variant>
#include <vector>

struct Character;
struct Player;

enum TriggerType {
  CHARACTER_TAKES_DAMAGE,
  CHARACTER_SURVIVES_DAMAGE,
  CHARACTER_DEATH,
  CHARACTER_ATTACKS,
  NUM_TRIGGERS
};

struct TriggerState {
  virtual TriggerType type() const = 0;
  virtual ~TriggerState() {}
};

namespace TriggerStates {

  struct DamageTaken : TriggerState {
    virtual TriggerType type() const {
      return CHARACTER_TAKES_DAMAGE;
    }

    std::shared_ptr<Player> owner;
    std::shared_ptr<Player> other;
    std::shared_ptr<Character> source;
    int damage;

    DamageTaken(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, std::shared_ptr<Character> src, int dmg)
        : owner(p1), other(p2), source(src), damage(dmg) {}
  };

  struct DamageSurvived : TriggerState {
    virtual TriggerType type() const {
      return CHARACTER_SURVIVES_DAMAGE;
    }

    std::shared_ptr<Player> owner;
    std::shared_ptr<Player> other;
    std::shared_ptr<Character> source;

    DamageSurvived(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, std::shared_ptr<Character> src)
        : owner(p1), other(p2), source(src) {}
  };

  struct CharacterKilled : TriggerState {
    virtual TriggerType type() const {
      return CHARACTER_DEATH;
    }

    std::shared_ptr<Player> owner;
    std::shared_ptr<Player> other;
    std::shared_ptr<Character> source;

    CharacterKilled(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, std::shared_ptr<Character> src)
        : owner(p1), other(p2), source(src) {}
  };

  struct CharacterAttacks : TriggerState {
    virtual TriggerType type() const {
      return CHARACTER_ATTACKS;
    }

    std::shared_ptr<Player> attacker;
    std::shared_ptr<Player> defender;
    std::shared_ptr<Character> attack_char;
    std::shared_ptr<Character> defend_char;

    CharacterAttacks(std::shared_ptr<Player> a, std::shared_ptr<Player> d, std::shared_ptr<Character> ac,
                     std::shared_ptr<Character> dc)
        : attacker(a), defender(d), attack_char(ac), defend_char(dc) {}
  };

}; // namespace TriggerStates

struct Trigger {
  virtual TriggerType type() const = 0;

  virtual std::vector<std::shared_ptr<Effect>> handle(std::shared_ptr<TriggerState>) = 0;
  virtual ~Trigger() {}
};

template <TriggerType T>
struct TypedTrigger : Trigger {
  virtual TriggerType type() const {
    return T;
  }
};


namespace LogTriggers {

  struct DamageTaken : TypedTrigger<CHARACTER_TAKES_DAMAGE> {
    virtual std::vector<std::shared_ptr<Effect>> handle(std::shared_ptr<TriggerState>);
  };

  struct DamageSurvived : TypedTrigger<CHARACTER_SURVIVES_DAMAGE> {
    virtual std::vector<std::shared_ptr<Effect>> handle(std::shared_ptr<TriggerState>);
  };

  struct CharacterKilled : TypedTrigger<CHARACTER_DEATH> {
    virtual std::vector<std::shared_ptr<Effect>> handle(std::shared_ptr<TriggerState>);
  };

  struct CharacterAttacks : TypedTrigger<CHARACTER_ATTACKS> {
    virtual std::vector<std::shared_ptr<Effect>> handle(std::shared_ptr<TriggerState>);
  };

}; // namespace LogTriggers