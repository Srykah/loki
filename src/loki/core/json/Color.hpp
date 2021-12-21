/*!
 * \file Color.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics/Color.hpp>
#include <charconv>
#include <nlohmann/json.hpp>
#include <string>

namespace loki::common {

inline std::string getHTMLColor(const sf::Color& color) {
  char str[10]{'#'};  // automatically null-terminated
  std::to_chars(str + 1, str + 3, color.r, 16);
  std::to_chars(str + 3, str + 5, color.g, 16);
  std::to_chars(str + 5, str + 7, color.b, 16);
  if (color.a != 255) {  // do not write alpha if fully opaque
    std::to_chars(str + 7, str + 9, color.a, 16);
  }
  return std::string{str};
}

inline sf::Color parseHTMLColor(const std::string& htmlCode) {
  sf::Color color;
  std::from_chars(htmlCode.c_str() + 1, htmlCode.c_str() + 3, color.r, 16);
  std::from_chars(htmlCode.c_str() + 3, htmlCode.c_str() + 5, color.g, 16);
  std::from_chars(htmlCode.c_str() + 5, htmlCode.c_str() + 7, color.b, 16);
  if (htmlCode.size() >= 9) {
    std::from_chars(htmlCode.c_str() + 7, htmlCode.c_str() + 9, color.a, 16);
  }
  return color;
}

}  // namespace loki::common

namespace nlohmann {

template <>
struct adl_serializer<sf::Color> {
  static void to_json(json& j, const sf::Color& color) {
    j = loki::common::getHTMLColor(color);
  }

  static void from_json(const json& j, sf::Color& color) {
    if (j.type() == detail::value_t::string) {
      color = loki::common::parseHTMLColor(j.get<std::string>());
    }
  }
};

}  // namespace nlohmann
