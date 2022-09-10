#pragma once

#include <SFML/Window/Mouse.hpp>
#include <nlohmann/json.hpp>

namespace nlohmann {

template <>
struct adl_serializer<sf::Mouse::Button> {
 private:
  static constexpr std::pair<sf::Mouse::Button, const char*>
      MOUSE_BUTTON_NAMES[] = {
#define LOKI_JSON_MOUSE_BUTTON_NAME(Button) {sf::Mouse::Button, #Button}
          LOKI_JSON_MOUSE_BUTTON_NAME(Left), LOKI_JSON_MOUSE_BUTTON_NAME(Right),
          LOKI_JSON_MOUSE_BUTTON_NAME(Middle),
          LOKI_JSON_MOUSE_BUTTON_NAME(XButton1),
          LOKI_JSON_MOUSE_BUTTON_NAME(XButton2)
#undef LOKI_JSON_MOUSE_BUTTON_NAME
      };

 public:
  static void to_json(json& j, sf::Mouse::Button button) {
    auto it = std::find_if(
        std::begin(MOUSE_BUTTON_NAMES), std::end(MOUSE_BUTTON_NAMES),
        [button](const auto& p) { return p.first == button; });
    if (it != std::end(MOUSE_BUTTON_NAMES)) {
      j = it->second;
    } else {
      j = nullptr;
    }
  }

  static void from_json(const json& j, sf::Mouse::Button& button) {
    auto it = std::find_if(std::begin(MOUSE_BUTTON_NAMES),
                           std::end(MOUSE_BUTTON_NAMES),
                           [&j](const auto& p) { return p.second == j; });
    if (it != std::end(MOUSE_BUTTON_NAMES)) {
      button = it->first;
    } else {
      button = sf::Mouse::ButtonCount;
    }
  }
};

}  // namespace nlohmann
