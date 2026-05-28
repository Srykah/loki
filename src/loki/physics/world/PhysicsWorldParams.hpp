#pragma once

#include <SFML/System/Vector2.hpp>

#include <loki/core/reflection/sfmlTypesInfo.hpp>

namespace loki::physics {

struct PhysicsWorldParams {
  sf::Vector2f gravity;
  float pixelsToMetersRatio = 10.f;
  int subStepCount = 4;

  LOKI_REFLECTION_CLASS_DECLARE(PhysicsWorldParams)
};

}  // namespace loki::physics

LOKI_REFLECTION_CLASS_BEGIN(loki::physics::PhysicsWorldParams)
LOKI_REFLECTION_CLASS_FIELD(gravity)
LOKI_REFLECTION_CLASS_FIELD(pixelsToMetersRatio)
LOKI_REFLECTION_CLASS_FIELD(subStepCount)
LOKI_REFLECTION_CLASS_END()