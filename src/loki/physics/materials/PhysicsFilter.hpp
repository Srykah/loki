#pragma once

#include <box2d/box2d.h>
#include <loki/core/reflection/classMacros.hpp>
#include <loki/core/reflection/basicTypesInfo.hpp>

namespace loki::physics {

struct PhysicsFilter {
  uint64_t categoryBits = B2_DEFAULT_CATEGORY_BITS;
  uint64_t maskBits = B2_DEFAULT_MASK_BITS;
  int groupIndex = 0;

  b2Filter toFilterDef() const;

  LOKI_REFLECTION_CLASS_DECLARE(PhysicsFilter)
};

}  // namespace loki::physics

LOKI_REFLECTION_CLASS_BEGIN(loki::physics::PhysicsFilter)
LOKI_REFLECTION_CLASS_FIELD(categoryBits)
LOKI_REFLECTION_CLASS_FIELD(maskBits)
LOKI_REFLECTION_CLASS_FIELD(groupIndex)
LOKI_REFLECTION_CLASS_END()