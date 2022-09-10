#include "InputMethod.hpp"

namespace loki::system {

bool operator&(InputMethod lhs, InputMethod rhs) {
  return static_cast<std::underlying_type_t<InputMethod>>(lhs) &
         static_cast<std::underlying_type_t<InputMethod>>(rhs);
}

JoystickId getJoystickId(InputMethod inputMethod) {
  return static_cast<JoystickId>(std::log2(
      static_cast<std::underlying_type_t<InputMethod>>(inputMethod) -
      static_cast<std::underlying_type_t<InputMethod>>(InputMethod::Joystick)));
}

}  // namespace loki::system
