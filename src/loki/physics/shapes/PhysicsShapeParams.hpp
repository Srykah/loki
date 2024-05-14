#pragma once

#include <box2d/b2_chain_shape.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_edge_shape.h>
#include <box2d/b2_polygon_shape.h>

#include <loki/core/reflection/classMacros.hpp>
#include <loki/core/runtimeObject/BaseObject.hpp>

#include "PhysicsShapeType.hpp"

namespace loki::physics {

struct PhysicsShapeParams : public core::BaseObject {
  virtual PhysicsShapeType getType() const = 0;
  virtual const b2Shape* getB2Shape() const = 0;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(PhysicsShapeParams)
};

struct CircleShapeParams final : public PhysicsShapeParams {
  PhysicsShapeType getType() const override { return PhysicsShapeType::Circle; }
  const b2Shape* getB2Shape() const override { return &circleShape; }

  b2CircleShape circleShape;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(CircleShapeParams)
};

struct EdgeShapeParams final : public PhysicsShapeParams {
  PhysicsShapeType getType() const override { return PhysicsShapeType::Edge; }
  const b2Shape* getB2Shape() const override { return &edgeShape; }

  b2EdgeShape edgeShape;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(EdgeShapeParams)
};

struct PolygonShapeParams final : public PhysicsShapeParams {
  PhysicsShapeType getType() const override { return PhysicsShapeType::Polygon; }
  const b2Shape* getB2Shape() const override { return &polygonShape; }

  b2PolygonShape polygonShape;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(PolygonShapeParams)
};

struct ChainShapeParams final : public PhysicsShapeParams {
  PhysicsShapeType getType() const override { return PhysicsShapeType::Chain; }
  const b2Shape* getB2Shape() const override { return &chainShape; }

  b2ChainShape chainShape;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(ChainShapeParams)
};

}  // namespace loki::physics

LOKI_REFLECTION_CLASS_BEGIN_NO_FACTORY(loki::physics::PhysicsShapeParams)
LOKI_REFLECTION_CLASS_PARENT(loki::physics::PhysicsShapeParams, loki::core::BaseObject)
LOKI_REFLECTION_CLASS_END_RTTI(loki::physics::PhysicsShapeParams)

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::physics::PhysicsShapeParams, loki::physics::CircleShapeParams)
LOKI_REFLECTION_CLASS_FIELD_CUSTOM(
    loki::core::getTypeInfo<float>(),
    "radius",
    true,
    [](void* obj) -> TmpObj {
      return TmpObj::fromPtrNonOwned(&static_cast<loki::physics::CircleShapeParams*>(obj)->circleShape.m_radius);
    },
    [](const void* obj) -> ConstTmpObj {
      return ConstTmpObj::fromPtrNonOwned(
          &static_cast<const loki::physics::CircleShapeParams*>(obj)->circleShape.m_radius);
    },
    [](void* obj, const void* data) -> void {
      static_cast<loki::physics::CircleShapeParams*>(obj)->circleShape.m_radius = *static_cast<const float*>(data);
    })
LOKI_REFLECTION_CLASS_END_RTTI(loki::physics::CircleShapeParams)

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::physics::PhysicsShapeParams, loki::physics::EdgeShapeParams)
LOKI_REFLECTION_CLASS_FIELD_CUSTOM(
    loki::core::getTypeInfo<float>(),
    "radius",
    true,
    [](void* obj) -> TmpObj {
      return TmpObj::fromPtrNonOwned(&static_cast<loki::physics::EdgeShapeParams*>(obj)->edgeShape.m_radius);
    },
    [](const void* obj) -> ConstTmpObj {
      return ConstTmpObj::fromPtrNonOwned(&static_cast<const loki::physics::EdgeShapeParams*>(obj)->edgeShape.m_radius);
    },
    [](void* obj, const void* data) -> void {
      static_cast<loki::physics::EdgeShapeParams*>(obj)->edgeShape.m_radius = *static_cast<const float*>(data);
    })
LOKI_REFLECTION_CLASS_END_RTTI(loki::physics::EdgeShapeParams)

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::physics::PhysicsShapeParams, loki::physics::PolygonShapeParams)
LOKI_REFLECTION_CLASS_FIELD_CUSTOM(
    loki::core::getTypeInfo<float>(),
    "radius",
    true,
    [](void* obj) -> TmpObj {
      return TmpObj::fromPtrNonOwned(&static_cast<loki::physics::PolygonShapeParams*>(obj)->polygonShape.m_radius);
    },
    [](const void* obj) -> ConstTmpObj {
      return ConstTmpObj::fromPtrNonOwned(
          &static_cast<const loki::physics::PolygonShapeParams*>(obj)->polygonShape.m_radius);
    },
    [](void* obj, const void* data) -> void {
      static_cast<loki::physics::PolygonShapeParams*>(obj)->polygonShape.m_radius = *static_cast<const float*>(data);
    })
LOKI_REFLECTION_CLASS_END_RTTI(loki::physics::PolygonShapeParams)

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::physics::PhysicsShapeParams, loki::physics::ChainShapeParams)
LOKI_REFLECTION_CLASS_FIELD_CUSTOM(
    loki::core::getTypeInfo<float>(),
    "radius",
    true,
    [](void* obj) -> TmpObj {
      return TmpObj::fromPtrNonOwned(&static_cast<loki::physics::ChainShapeParams*>(obj)->chainShape.m_radius);
    },
    [](const void* obj) -> ConstTmpObj {
      return ConstTmpObj::fromPtrNonOwned(
          &static_cast<const loki::physics::ChainShapeParams*>(obj)->chainShape.m_radius);
    },
    [](void* obj, const void* data) -> void {
      static_cast<loki::physics::ChainShapeParams*>(obj)->chainShape.m_radius = *static_cast<const float*>(data);
    })
LOKI_REFLECTION_CLASS_END_RTTI(loki::physics::ChainShapeParams)