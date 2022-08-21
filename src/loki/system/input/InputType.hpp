#pragma once

#include <SFML/Window/Event.hpp>
#include <nlohmann/json.hpp>
#include <variant>

namespace loki::system {

using MouseButtonTrigger = sf::Mouse::Button;
enum JoystickButtonTrigger : unsigned int;
using KeyTrigger = sf::Keyboard::Key;
struct JoystickAxisTrigger {
  sf::Joystick::Axis axis;
  enum class Direction { POSITIVE, NEGATIVE, BOTH } direction;
  float deadZone = 30.f;  // [0; 100]
};
using InputTrigger = std::variant<MouseButtonTrigger,
                                  JoystickButtonTrigger,
                                  KeyTrigger,
                                  JoystickAxisTrigger>;

InputTrigger loadTrigger(const nlohmann::json& triggerDatum);

}  // namespace loki::system