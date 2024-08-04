#include "InputMethod.hpp"

#include <type_traits>

namespace loki::system {

JoystickId getJoystickId(InputMethod inputMethod) {
  return static_cast<JoystickId>(std::log2(static_cast<std::underlying_type_t<InputMethod>>(inputMethod) -
                                           static_cast<std::underlying_type_t<InputMethod>>(InputMethod::Joystick)));
}

}  // namespace loki::system
