#include "gdextension_bindings.h"

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#define WRAP_NOPARAMS(Cls, Param, T, M, ...) \
  T Cls::M() __VA_ARGS__ {                   \
    return Param->M();                       \
  }

#define WRAP_ONEPARAM(Cls, Param, T, M, T1, ...) \
  T Cls::M(T1 x) __VA_ARGS__ {                   \
    return Param->M(x);                          \
  }

WRAP_NOPARAMS(gCharacter, ch, int, getAttack, const)
WRAP_NOPARAMS(gCharacter, ch, int, getHealth, const)
WRAP_NOPARAMS(gCharacter, ch, int, getBaseHealth, const)
WRAP_NOPARAMS(gCharacter, ch, bool, golden, const)
WRAP_NOPARAMS(gCharacter, ch, bool, dead, const)
WRAP_NOPARAMS(gCharacter, ch, bool, alive, const)

WRAP_NOPARAMS(gPlayer, pl, int, getHealth, const)
WRAP_NOPARAMS(gPlayer, pl, bool, dead, const)
WRAP_NOPARAMS(gPlayer, pl, bool, alive, const)

WRAP_ONEPARAM(gCharacter, ch, void, setAttack, int)
WRAP_ONEPARAM(gCharacter, ch, void, setHealth, int)
WRAP_ONEPARAM(gCharacter, ch, void, takeDamage, int)

WRAP_ONEPARAM(gPlayer, pl, void, setHealth, int)
WRAP_ONEPARAM(gPlayer, pl, void, takeDamage, int)

godot::Ref<gCharacter> gPlayer::getCharacter(int position) const {
  return godot::Ref<gCharacter>(memnew(gCharacter(pl->characters[position - 1]))); // TODO
}

void gCharacter::_bind_methods() {
  using namespace godot;
  ClassDB::bind_method(D_METHOD("get_attack"), &gCharacter::getAttack);
  ClassDB::bind_method(D_METHOD("set_attack", "newvalue"), &gCharacter::setAttack);
  ADD_PROPERTY(PropertyInfo(Variant::INT, "attack"), "set_attack", "get_attack");

  ClassDB::bind_method(D_METHOD("get_health"), &gCharacter::getHealth);
  ClassDB::bind_method(D_METHOD("set_health", "newvalue"), &gCharacter::setHealth);
  ADD_PROPERTY(PropertyInfo(Variant::INT, "health"), "set_health", "get_health");

  ClassDB::bind_method(D_METHOD("get_base_health"), &gCharacter::getBaseHealth);

  ClassDB::bind_method(D_METHOD("take_damage", "amount"), &gCharacter::takeDamage);

  ClassDB::bind_method(D_METHOD("is_golden"), &gCharacter::golden);
  ClassDB::bind_method(D_METHOD("is_dead"), &gCharacter::dead);
  ClassDB::bind_method(D_METHOD("is_alive"), &gCharacter::alive);
}

void gPlayer::_bind_methods() {
  using namespace godot;
  ClassDB::bind_method(D_METHOD("get_health"), &gPlayer::getHealth);
  ClassDB::bind_method(D_METHOD("set_health", "newvalue"), &gPlayer::setHealth);
  ADD_PROPERTY(PropertyInfo(Variant::INT, "health"), "set_health", "get_health");

  ClassDB::bind_method(D_METHOD("take_damage", "amount"), &gPlayer::takeDamage);

  ClassDB::bind_method(D_METHOD("is_dead"), &gPlayer::dead);
  ClassDB::bind_method(D_METHOD("is_alive"), &gPlayer::alive);
}
