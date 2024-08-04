#pragma once

#include <cmath>

#include <loki/core/utils/EnumAsBitField.hpp>

namespace loki::system {

using JoystickId = unsigned int;

enum class InputMethod {
  None = 0,
  Keyboard = 1 << 0,
  Mouse = 1 << 1,
  Joystick = 1 << 2,
  KeyboardAndMouse = Keyboard | Mouse,
  Joystick0 = 1 << 3 | Joystick,
  Joystick1 = 1 << 4 | Joystick,
  Joystick2 = 1 << 5 | Joystick,
  Joystick3 = 1 << 6 | Joystick,
  Joystick4 = 1 << 7 | Joystick,
  Joystick5 = 1 << 8 | Joystick,
  Joystick6 = 1 << 9 | Joystick,
  Joystick7 = 1 << 10 | Joystick,
};

LOKI_ENUM_AS_BITFIELD(InputMethod)

JoystickId getJoystickId(InputMethod inputMethod);

}  // namespace loki::system