#pragma once

#include <box2d/b2_body.h>

namespace loki::physics {

enum class PhysicsBodyType : std::underlying_type_t<b2BodyType> {
  Static = b2_staticBody,
  Kinematic = b2_kinematicBody,
  Dynamic = b2_dynamicBody
};

}

LOKI_REFLECTION_ENUM_BEGIN(loki::physics::PhysicsBodyType)
LOKI_REFLECTION_ENUMERATOR(loki::physics::PhysicsBodyType, Static)
LOKI_REFLECTION_ENUMERATOR(loki::physics::PhysicsBodyType, Kinematic)
LOKI_REFLECTION_ENUMERATOR(loki::physics::PhysicsBodyType, Dynamic)
LOKI_REFLECTION_ENUM_END()