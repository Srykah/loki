#pragma once

#include <box2d/box2d.h>

#include <loki/core/reflection/classMacros.hpp>
#include <loki/core/reflection/enumMacros.hpp>
#include <loki/physics/bodies/PhysicsBodyType.hpp>

namespace loki::physics {

struct PhysicsBodyParams {
  PhysicsBodyType type = PhysicsBodyType::Static;
  float linearDamping = 0.0f;
  float angularDamping = 0.0f;
  float gravityScale = 1.0f;
  float sleepThreshold = 0.05f;
  bool enableSleep = true;
  bool isAwake = true;
  bool fixedRotation = false;
  bool isBullet = false;
  bool isEnabled = true;
  bool allowFastRotation = false;

  b2BodyDef toBodyDef() const;

  LOKI_REFLECTION_CLASS_DECLARE(PhysicsBodyParams)
};

}  // namespace loki::physics

LOKI_REFLECTION_CLASS_BEGIN(loki::physics::PhysicsBodyParams)
LOKI_REFLECTION_CLASS_FIELD(type)
LOKI_REFLECTION_CLASS_FIELD(linearDamping)
LOKI_REFLECTION_CLASS_FIELD(angularDamping)
LOKI_REFLECTION_CLASS_FIELD(gravityScale)
LOKI_REFLECTION_CLASS_FIELD(sleepThreshold)
LOKI_REFLECTION_CLASS_FIELD(enableSleep)
LOKI_REFLECTION_CLASS_FIELD(isAwake)
LOKI_REFLECTION_CLASS_FIELD(fixedRotation)
LOKI_REFLECTION_CLASS_FIELD(isBullet)
LOKI_REFLECTION_CLASS_FIELD(isEnabled)
LOKI_REFLECTION_CLASS_FIELD(allowFastRotation)
LOKI_REFLECTION_CLASS_END()