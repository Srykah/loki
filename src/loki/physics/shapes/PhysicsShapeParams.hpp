#pragma once

#include <box2d/box2d.h>

#include <loki/core/reflection/basicTypesInfo.hpp>
#include <loki/core/reflection/classMacros.hpp>
#include <loki/core/reflection/sfmlTypesInfo.hpp>
#include <loki/core/rtti/BaseObject.hpp>
#include <loki/physics/materials/PhysicsFilter.hpp>
#include <loki/physics/materials/PhysicsMaterial.hpp>
#include <loki/physics/shapes/PhysicsShapeType.hpp>

namespace loki::physics {

struct PhysicsShapeParams : public core::BaseObject {
  virtual PhysicsShapeType getType() const = 0;
  virtual b2ShapeId createShape(b2BodyId bodyId) const = 0;

  PhysicsMaterial material;
  float density = 1.f;
  PhysicsFilter filter;
  bool isSensor = false;
  bool enableSensorEvents = false;
  bool enableContactEvents = false;
  bool enableHitEvents = false;
  bool enablePreSolveEvents = false;
  bool invokeContactCreation = false;
  bool updateBodyMass = true;
  sf::Transformable offset;

  b2ShapeDef toShapeDef() const;

  LOKI_RTTI_CLASS_DECLARE(PhysicsShapeParams)
};

struct CircleShapeParams final : public PhysicsShapeParams {
  PhysicsShapeType getType() const override { return PhysicsShapeType::Circle; }
  b2ShapeId createShape(b2BodyId bodyId) const override;

  float radius = 0.f;

  LOKI_RTTI_CLASS_DECLARE(CircleShapeParams)
};

struct CapsuleShapeParams final : public PhysicsShapeParams {
  PhysicsShapeType getType() const override { return PhysicsShapeType::Capsule; }
  b2ShapeId createShape(b2BodyId bodyId) const override;

  sf::Vector2f center1;
  sf::Vector2f center2;
  float radius = 0.f;

  LOKI_RTTI_CLASS_DECLARE(CapsuleShapeParams)
};

struct SegmentShapeParams final : public PhysicsShapeParams {
  PhysicsShapeType getType() const override { return PhysicsShapeType::Segment; }
  b2ShapeId createShape(b2BodyId bodyId) const override;

  sf::Vector2f point1;
  sf::Vector2f point2;

  LOKI_RTTI_CLASS_DECLARE(SegmentShapeParams)
};

struct PolygonShapeParams final : public PhysicsShapeParams {
  PhysicsShapeType getType() const override { return PhysicsShapeType::Polygon; }
  b2ShapeId createShape(b2BodyId bodyId) const override;

  std::vector<sf::Vector2f> points;
  float radius = 0.f;

  LOKI_RTTI_CLASS_DECLARE(PolygonShapeParams)
};

struct BoxShapeParams final : public PhysicsShapeParams {
  PhysicsShapeType getType() const override { return PhysicsShapeType::Polygon; }
  b2ShapeId createShape(b2BodyId bodyId) const override;

  sf::Vector2f halfSize;
  float radius = 0.f;

  LOKI_RTTI_CLASS_DECLARE(BoxShapeParams)
};

struct ChainShapeParams final : public PhysicsShapeParams {
  PhysicsShapeType getType() const override { return PhysicsShapeType::Chain; }
  b2ShapeId createShape(b2BodyId bodyId) const override;

  std::vector<sf::Vector2f> points;
  bool isLoop = false;

  LOKI_RTTI_CLASS_DECLARE(ChainShapeParams)
};

}  // namespace loki::physics

LOKI_REFLECTION_CLASS_BEGIN_RTTI_NO_FACTORY(loki::physics::PhysicsShapeParams)
LOKI_REFLECTION_CLASS_FIELD(material)
LOKI_REFLECTION_CLASS_FIELD(density)
LOKI_REFLECTION_CLASS_FIELD(filter)
LOKI_REFLECTION_CLASS_FIELD(isSensor)
LOKI_REFLECTION_CLASS_FIELD(enableSensorEvents)
LOKI_REFLECTION_CLASS_FIELD(enableContactEvents)
LOKI_REFLECTION_CLASS_FIELD(enableHitEvents)
LOKI_REFLECTION_CLASS_FIELD(enablePreSolveEvents)
LOKI_REFLECTION_CLASS_FIELD(invokeContactCreation)
LOKI_REFLECTION_CLASS_FIELD(updateBodyMass)
LOKI_REFLECTION_CLASS_FIELD(offset)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::physics::PhysicsShapeParams)

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::physics::CircleShapeParams, loki::physics::PhysicsShapeParams)
LOKI_REFLECTION_CLASS_FIELD(radius)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::physics::CircleShapeParams)

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::physics::CapsuleShapeParams, loki::physics::PhysicsShapeParams)
LOKI_REFLECTION_CLASS_FIELD(center1)
LOKI_REFLECTION_CLASS_FIELD(center2)
LOKI_REFLECTION_CLASS_FIELD(radius)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::physics::CapsuleShapeParams)

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::physics::SegmentShapeParams, loki::physics::PhysicsShapeParams)
LOKI_REFLECTION_CLASS_FIELD(point1)
LOKI_REFLECTION_CLASS_FIELD(point2)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::physics::SegmentShapeParams)

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::physics::PolygonShapeParams, loki::physics::PhysicsShapeParams)
LOKI_REFLECTION_CLASS_FIELD(points)
LOKI_REFLECTION_CLASS_FIELD(radius)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::physics::PolygonShapeParams)

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::physics::BoxShapeParams, loki::physics::PhysicsShapeParams)
LOKI_REFLECTION_CLASS_FIELD(halfSize)
LOKI_REFLECTION_CLASS_FIELD(radius)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::physics::BoxShapeParams)

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::physics::ChainShapeParams, loki::physics::PhysicsShapeParams)
// todo
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::physics::ChainShapeParams)
