/*!
 * \file Rect.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <nlohmann/json.hpp>

namespace nlohmann {

template <typename T>
struct adl_serializer<sf::Rect<T>> {
  static void to_json(json& j, const sf::Rect<T>& rect) {
    j = json{
        {"left", rect.left},
        {"top", rect.top},
        {"width", rect.width},
        {"height", rect.height},
    };
  }

  static void from_json(const json& j, sf::Rect<T>& rect) {
    j.at("left").get_to(rect.left);
    j.at("top").get_to(rect.top);
    j.at("width").get_to(rect.width);
    j.at("height").get_to(rect.height);
  }
};

}  // namespace nlohmann
