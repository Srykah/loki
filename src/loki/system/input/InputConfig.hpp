#pragma once

#include <map>
#include <variant>
#include <SFML/Window/Event.hpp>

#if 0
#include <nlohmann/json.hpp>
#include <loki/core/json/Joystick.hpp>
#include <loki/core/json/Keyboard.hpp>
#include <loki/core/json/Mouse.hpp>
#include <loki/core/json/Variant.hpp>
#endif

namespace loki::system {

using KeyTrigger = sf::Keyboard::Key;

using MouseButtonTrigger = sf::Mouse::Button;

struct JoystickAxisTrigger {
  sf::Joystick::Axis axis;
  enum class Direction { NEGATIVE = -1, BOTH = 0, POSITIVE = +1 } direction;
};

#if 0
NLOHMANN_JSON_SERIALIZE_ENUM(JoystickAxisTrigger::Direction,
                             {{JoystickAxisTrigger::Direction::BOTH, 0},
                              {JoystickAxisTrigger::Direction::NEGATIVE, -1},
                              {JoystickAxisTrigger::Direction::POSITIVE, +1}})
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(JoystickAxisTrigger, axis, direction)
#endif

using JoystickButtonTrigger = unsigned int;

using InputTrigger = std::variant<KeyTrigger,
                                  MouseButtonTrigger,
                                  JoystickAxisTrigger,
                                  JoystickButtonTrigger>;

using InputId = std::string;
using InputConfig = std::map<InputId, std::vector<InputTrigger>>;

}  // namespace loki::system