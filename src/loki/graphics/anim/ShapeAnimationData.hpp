#pragma once

#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Time.hpp>
#include <nlohmann/json.hpp>

#include <loki/core/json/Time.hpp>
#include <loki/core/json/Vector2.hpp>
#include <loki/core/math/Interpolate.hpp>
#include <loki/core/math/Vector4.hpp>

namespace loki::gfx {

struct ShapeAnimationData {
  sf::Time duration;
  bool repeat;
  core::Interpolation<sf::Time, sf::Vector2f> ipOrigin;
  core::Interpolation<sf::Time, sf::Vector2f> ipPos;
  core::Interpolation<sf::Time, float> ipRot;
  core::Interpolation<sf::Time, sf::Vector2f> ipScale;
  core::Interpolation<sf::Time, core::Vector4f> ipColor;
  core::Interpolation<sf::Time, core::Vector4f> ipTexRect;
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

}  // namespace loki::gfx
