#pragma once

#include <box2d/box2d.h>

#include <loki/core/reflection/basicTypesInfo.hpp>
#include <loki/core/reflection/classMacros.hpp>

namespace loki::physics {

struct PhysicsMaterial {
  float friction = 0.6f;
  float restitution = 0.f;
  float rollingResistance = 0.f;
  float tangentSpeed = 0.f;

  b2SurfaceMaterial toSurfaceMaterialDef() const;

  LOKI_REFLECTION_CLASS_DECLARE(PhysicsMaterial)
};

}  // namespace loki::physics

LOKI_REFLECTION_CLASS_BEGIN(loki::physics::PhysicsMaterial)
LOKI_REFLECTION_CLASS_FIELD(friction)
LOKI_REFLECTION_CLASS_FIELD(restitution)
LOKI_REFLECTION_CLASS_FIELD(rollingResistance)
LOKI_REFLECTION_CLASS_FIELD(tangentSpeed)
LOKI_REFLECTION_CLASS_END()
