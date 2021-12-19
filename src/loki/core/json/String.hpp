/*!
 * \file String.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/System/String.hpp>
#include <nlohmann/json.hpp>

namespace nlohmann {

template <>
struct adl_serializer<sf::String> {
  static void to_json(json& j, const sf::String& str) { j = str.toUtf8(); }

  static void from_json(const json& j, sf::String& str) {
    auto json_str = j.get<std::string>();
    str = sf::String::fromUtf8(json_str.begin(), json_str.end());
  }
};

}  // namespace nlohmann
