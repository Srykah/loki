#pragma once

#include <box2d/b2_body.h>

#include <loki/core/reflection/classMacros.hpp>
#include <loki/core/reflection/enumMacros.hpp>
#include <loki/physics/bodies/PhysicsBodyType.hpp>
#include <loki/physics/shapes/PhysicsFixtureParams.hpp>

namespace loki::physics {

struct PhysicsBodyParams {
  PhysicsBodyType type = PhysicsBodyType::Static;
  float linearDamping = 0.0f;
  float angularDamping = 0.0f;
  float gravityScale = 1.0f;
  bool fixedRotation = false;
  bool bullet = false;

  b2BodyDef toBodyDef() const;

  LOKI_REFLECTION_CLASS_DECLARE(PhysicsBodyParams)
};

}  // namespace loki::physics

LOKI_REFLECTION_CLASS_BEGIN(loki::physics::PhysicsBodyParams)
LOKI_REFLECTION_CLASS_FIELD(type)
LOKI_REFLECTION_CLASS_FIELD(linearDamping)
LOKI_REFLECTION_CLASS_FIELD(angularDamping)
LOKI_REFLECTION_CLASS_FIELD(gravityScale)
LOKI_REFLECTION_CLASS_FIELD(fixedRotation)
LOKI_REFLECTION_CLASS_FIELD(bullet)
LOKI_REFLECTION_CLASS_END()