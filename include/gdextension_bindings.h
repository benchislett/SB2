#pragma once

#include "character.h"
#include "player.h"

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/godot.hpp>

struct gCharacter : godot::RefCounted {
  GDCLASS(gCharacter, godot::RefCounted)

  std::shared_ptr<Character> ch;

  gCharacter() {}
  gCharacter(std::shared_ptr<Character> c) : ch(c) {}

  int getAttack() const;
  int getHealth() const;
  int getBaseHealth() const;
  void setAttack(int);
  void setHealth(int);

  void takeDamage(int);

  bool golden() const;
  bool dead() const;
  bool alive() const;

  static void _bind_methods();
};

struct gPlayer : godot::RefCounted {
  GDCLASS(gPlayer, godot::RefCounted)

  std::shared_ptr<Player> pl;

  int getHealth() const;
  void setHealth(int);
  void takeDamage(int);

  bool dead() const;
  bool alive() const;

  godot::Ref<gCharacter> getCharacter(int) const;

  void kill(int);

  static void _bind_methods();
};
