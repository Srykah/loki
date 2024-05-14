#pragma once

#include <box2d/b2_fixture.h>

#include <loki/physics/shapes/ChainShape.hpp>
#include <loki/physics/shapes/CircleShape.hpp>
#include <loki/physics/shapes/EdgeShape.hpp>
#include <loki/physics/shapes/PhysicsShapeType.hpp>
#include <loki/physics/shapes/PolygonShape.hpp>

namespace loki::physics {
class PhysicsBody;

// encapsulates both a fixture and its shape
class PhysicsShape {
 public:
  explicit PhysicsShape(b2Fixture* fixture, PhysicsBody* parentBody);

  [[nodiscard]] PhysicsShapeType getShapeType() const;
  [[nodiscard]] CircleShape getAsCircleShape();
  [[nodiscard]] EdgeShape getAsEdgeShape();
  [[nodiscard]] PolygonShape getAsPolygonShape();
  [[nodiscard]] ChainShape getAsChainShape();

 private:
  PhysicsBody* parentBody;
  b2Fixture* fixture;
};

}  // namespace loki::physics