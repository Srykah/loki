#pragma once

#include <SFML/System/Vector2.hpp>
#include <nlohmann/json.hpp>

namespace nlohmann {

template <typename T>
struct adl_serializer<sf::Vector2<T>> {
  static void to_json(json& j, const sf::Vector2<T>& vector2) {
    j = json{{"x", vector2.x}, {"y", vector2.y}};
  }

  static void from_json(const json& j, sf::Vector2<T>& vector2) {
    j.at("x").get_to(vector2.x);
    j.at("y").get_to(vector2.y);
  }
};

}  // namespace nlohmann
