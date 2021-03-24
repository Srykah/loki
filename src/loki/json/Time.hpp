/*!
 * \file Time.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/System/Time.hpp>
#include <nlohmann/json.hpp>

namespace nlohmann {

template <>
struct adl_serializer<sf::Time> {
  static void to_json(json& j, const sf::Time& time) {
    j = time.asMilliseconds();
  }

  static void from_json(const json& j, sf::Time& time) {
    time = sf::milliseconds(j.get<sf::Int32>());
  }
};

}  // namespace nlohmann
