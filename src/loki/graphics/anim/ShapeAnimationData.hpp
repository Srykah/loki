#pragma once

#include <SFML/System/Time.hpp>

#include <loki/core/math/Interpolate.hpp>
#include <loki/core/math/Vector4.hpp>
#include <loki/core/reflection/classMacros.hpp>
#include <loki/core/reflection/sfmlTypesInfo.hpp>

namespace loki::graphics {

struct ShapeAnimationData {
  sf::Time duration;
  bool repeat;
  core::InterpolationData<sf::Time, sf::Vector2f> ipOrigin;
  core::InterpolationData<sf::Time, sf::Vector2f> ipPos;
  core::InterpolationData<sf::Time, float> ipRot;
  core::InterpolationData<sf::Time, sf::Vector2f> ipScale;
  core::InterpolationData<sf::Time, core::Vector4f> ipColor;
  core::InterpolationData<sf::Time, core::Vector4f> ipTexRect;

  LOKI_REFLECTION_CLASS_DECLARE(ShapeAnimationData)
};

}  // namespace loki::graphics

LOKI_REFLECTION_CLASS_BEGIN(loki::graphics::ShapeAnimationData)
LOKI_REFLECTION_CLASS_FIELD(loki::graphics::ShapeAnimationData, duration)
LOKI_REFLECTION_CLASS_FIELD(loki::graphics::ShapeAnimationData, repeat)
LOKI_REFLECTION_CLASS_FIELD(loki::graphics::ShapeAnimationData, ipOrigin)
LOKI_REFLECTION_CLASS_FIELD(loki::graphics::ShapeAnimationData, ipPos)
LOKI_REFLECTION_CLASS_FIELD(loki::graphics::ShapeAnimationData, ipRot)
LOKI_REFLECTION_CLASS_FIELD(loki::graphics::ShapeAnimationData, ipScale)
LOKI_REFLECTION_CLASS_FIELD(loki::graphics::ShapeAnimationData, ipColor)
LOKI_REFLECTION_CLASS_FIELD(loki::graphics::ShapeAnimationData, ipTexRect)
LOKI_REFLECTION_CLASS_END()