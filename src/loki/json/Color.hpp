/*!
 * \file Color.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <nlohmann/json.hpp>
#include <SFML/Graphics/Color.hpp>
#include <string>

namespace loki::common {

std::string getHTMLColor(const sf::Color& color);
sf::Color parseHTMLColor(const std::string& htmlCode);

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
