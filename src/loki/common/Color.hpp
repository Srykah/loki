/*!
 * \file Color.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <charconv>

namespace loki::common {
inline sf::Color parseHTMLColor(const std::string& htmlCode) {
  sf::Color color;
  std::from_chars(htmlCode.c_str() + 1, htmlCode.c_str() + 3, color.r, 16);
  std::from_chars(htmlCode.c_str() + 3, htmlCode.c_str() + 5, color.g, 16);
  std::from_chars(htmlCode.c_str() + 5, htmlCode.c_str() + 7, color.b, 16);
  return color;
}
}  // namespace loki::common