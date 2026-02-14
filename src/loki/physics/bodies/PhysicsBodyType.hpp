#pragma once

#include <box2d/box2d.h>

namespace loki::physics {

enum class PhysicsBodyType : std::underlying_type_t<b2BodyType> {
  Static = b2_staticBody,
  Kinematic = b2_kinematicBody,
  Dynamic = b2_dynamicBody
};

}

LOKI_REFLECTION_ENUM_BEGIN(loki::physics::PhysicsBodyType)
LOKI_REFLECTION_ENUMERATOR(Static)
LOKI_REFLECTION_ENUMERATOR(Kinematic)
LOKI_REFLECTION_ENUMERATOR(Dynamic)
LOKI_REFLECTION_ENUM_END()