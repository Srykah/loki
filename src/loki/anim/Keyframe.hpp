/*!
 * \file Keyframe.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once
#include <loki/json/All_old.hpp>
#include <nlohmann/json.hpp>
#include <optional>

namespace loki::anim {

struct Keyframe {
  std::optional<sf::Vector2f> origin;
  std::optional<sf::Vector2f> position;
  std::optional<float> rotation;
  std::optional<sf::Vector2f> scale;
  std::optional<sf::Color> color;
  std::optional<sf::IntRect> textureRect;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Keyframe, origin, position, rotation, scale, color, textureRect)

}
