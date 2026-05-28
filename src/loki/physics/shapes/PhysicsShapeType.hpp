#pragma once

#include <type_traits>

#include <box2d/box2d.h>

#include <loki/core/reflection/enumMacros.hpp>

namespace loki::physics {

enum class PhysicsShapeType : std::underlying_type_t<b2ShapeType> {
  Circle = b2ShapeType::b2_circleShape,
  Capsule = b2ShapeType::b2_capsuleShape,
  Segment = b2ShapeType::b2_segmentShape,
  Polygon = b2ShapeType::b2_polygonShape,
  Chain = b2ShapeType::b2_chainSegmentShape,
};

}

LOKI_REFLECTION_ENUM_BEGIN(loki::physics::PhysicsShapeType)
LOKI_REFLECTION_ENUMERATOR(Circle)
LOKI_REFLECTION_ENUMERATOR(Capsule)
LOKI_REFLECTION_ENUMERATOR(Segment)
LOKI_REFLECTION_ENUMERATOR(Polygon)
LOKI_REFLECTION_ENUMERATOR(Chain)
LOKI_REFLECTION_ENUM_END()