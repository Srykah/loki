#pragma once

#include <SFML/Window/Joystick.hpp>
#include <nlohmann/json.hpp>

namespace nlohmann {

template <>
struct adl_serializer<sf::Joystick::Axis> {
 private:
  static constexpr std::pair<sf::Joystick::Axis, const char*>
      JOYSTICK_AXIS_NAMES[] = {
#define LOKI_JSON_JOYSTICK_AXIS_NAME(Axis) {sf::Joystick::Axis, #Axis}
          LOKI_JSON_JOYSTICK_AXIS_NAME(X),
          LOKI_JSON_JOYSTICK_AXIS_NAME(Y),
          LOKI_JSON_JOYSTICK_AXIS_NAME(Z),
          LOKI_JSON_JOYSTICK_AXIS_NAME(R),
          LOKI_JSON_JOYSTICK_AXIS_NAME(U),
          LOKI_JSON_JOYSTICK_AXIS_NAME(V),
          LOKI_JSON_JOYSTICK_AXIS_NAME(PovX),
          LOKI_JSON_JOYSTICK_AXIS_NAME(PovY)
#undef LOKI_JSON_JOYSTICK_AXIS_NAME
      };

 public:
  static void to_json(json& j, sf::Joystick::Axis axis) {
    auto it = std::find_if(std::begin(JOYSTICK_AXIS_NAMES),
                           std::end(JOYSTICK_AXIS_NAMES),
                           [axis](const auto& p) { return p.first == axis; });
    if (it != std::end(JOYSTICK_AXIS_NAMES)) {
      j = it->second;
    } else {
      j = nullptr;
    }
  }

  static void from_json(const json& j, sf::Joystick::Axis& axis) {
    auto it = std::find_if(std::begin(JOYSTICK_AXIS_NAMES),
                           std::end(JOYSTICK_AXIS_NAMES),
                           [&j](const auto& p) { return p.second == j; });
    if (it != std::end(JOYSTICK_AXIS_NAMES)) {
      axis = it->first;
    } else {
      axis = static_cast<sf::Joystick::Axis>(-1);
    }
  }
};

}  // namespace nlohmann
