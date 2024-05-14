#pragma once

#include <SFML/System/Vector2.hpp>

#include <loki/core/reflection/sfmlTypesInfo.hpp>

namespace loki::physics {

struct PhysicsWorldParams {
  sf::Vector2f gravity;
  float pixelsToMetersRatio = 10.f;
  int velocityIterationCount = 8;
  int positionIterationCount = 3;

  LOKI_REFLECTION_CLASS_DECLARE(PhysicsWorldParams)
};

}  // namespace loki::physics

LOKI_REFLECTION_CLASS_BEGIN(loki::physics::PhysicsWorldParams)
LOKI_REFLECTION_CLASS_FIELD(loki::physics::PhysicsWorldParams, gravity)
LOKI_REFLECTION_CLASS_FIELD(loki::physics::PhysicsWorldParams, pixelsToMetersRatio)
LOKI_REFLECTION_CLASS_FIELD(loki::physics::PhysicsWorldParams, velocityIterationCount)
LOKI_REFLECTION_CLASS_FIELD(loki::physics::PhysicsWorldParams, positionIterationCount)
LOKI_REFLECTION_CLASS_END()