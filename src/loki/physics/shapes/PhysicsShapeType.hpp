#pragma once

#include <type_traits>

#include <box2d/b2_shape.h>

#include <loki/core/reflection/enumMacros.hpp>

namespace loki::physics {

enum class PhysicsShapeType : std::underlying_type_t<b2Shape::Type> {
  Circle = b2Shape::Type::e_circle,
  Edge = b2Shape::Type::e_edge,
  Polygon = b2Shape::Type::e_polygon,
  Chain = b2Shape::Type::e_chain,
};

}

LOKI_REFLECTION_ENUM_BEGIN(loki::physics::PhysicsShapeType)
LOKI_REFLECTION_ENUMERATOR(loki::physics::PhysicsShapeType, Circle)
LOKI_REFLECTION_ENUMERATOR(loki::physics::PhysicsShapeType, Edge)
LOKI_REFLECTION_ENUMERATOR(loki::physics::PhysicsShapeType, Polygon)
LOKI_REFLECTION_ENUMERATOR(loki::physics::PhysicsShapeType, Chain)
LOKI_REFLECTION_ENUM_END()