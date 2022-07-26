/*!
 * \file Animation.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Time.hpp>
#include <loki/core/json/All.hpp>
#include <loki/core/math/Interpolate.hpp>
#include <loki/core/math/Vector4.hpp>
#include <nlohmann/json.hpp>

namespace loki::anim {

struct ShapeAnimationData {
  sf::Time duration;
  bool repeat;
  math::Interpolation<sf::Time, sf::Vector2f> ipOrigin;
  math::Interpolation<sf::Time, sf::Vector2f> ipPos;
  math::Interpolation<sf::Time, float> ipRot;
  math::Interpolation<sf::Time, sf::Vector2f> ipScale;
  math::Interpolation<sf::Time, math::Vector4f> ipColor;
  math::Interpolation<sf::Time, math::Vector4f> ipTexRect;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ShapeAnimationData,
                                   duration,
                                   repeat,
                                   ipOrigin,
                                   ipPos,
                                   ipRot,
                                   ipScale,
                                   ipColor,
                                   ipTexRect);

}  // namespace loki::anim
