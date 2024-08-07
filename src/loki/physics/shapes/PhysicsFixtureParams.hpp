#pragma once

#include <box2d/b2_fixture.h>

#include <loki/core/reflection/classMacros.hpp>
#include <loki/physics/shapes/PhysicsShapeParams.hpp>

namespace loki::physics {

struct PhysicsFixtureParams {
  float friction = 0.2f;
  float restitution = 0.0f;
  float restitutionThreshold = 1.0f * b2_lengthUnitsPerMeter;
  float density = 0.0f;
  bool isSensor = false;
  std::shared_ptr<PhysicsShapeParams> shapeParams;

  b2FixtureDef toFixtureDef() const;

  LOKI_REFLECTION_CLASS_DECLARE(PhysicsFixtureParams)
};

}  // namespace loki::physics

LOKI_REFLECTION_CLASS_BEGIN(loki::physics::PhysicsFixtureParams)
LOKI_REFLECTION_CLASS_FIELD(friction)
LOKI_REFLECTION_CLASS_FIELD(restitution)
LOKI_REFLECTION_CLASS_FIELD(restitutionThreshold)
LOKI_REFLECTION_CLASS_FIELD(density)
LOKI_REFLECTION_CLASS_FIELD(isSensor)
LOKI_REFLECTION_CLASS_FIELD(shapeParams)
LOKI_REFLECTION_CLASS_END()