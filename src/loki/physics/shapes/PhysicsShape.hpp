#pragma once

#include <box2d/box2d.h>
#include <loki/physics/shapes/PhysicsShapeParams.hpp>
#include <loki/physics/shapes/PhysicsShapeType.hpp>

namespace loki::physics {

class PhysicsShape {
 private:
  friend class PhysicsBody;
  explicit PhysicsShape(PhysicsBody* parentBody, const PhysicsShapeParams& shapeParams, const sf::Transformable& trs);

 public:
  ~PhysicsShape();

 public:
  [[nodiscard]] PhysicsShapeType getShapeType() const;

 private:
  PhysicsBody* parentBody = nullptr;
  b2ShapeId shapeId = b2_nullShapeId;
  bool isChain = false;
};

}  // namespace loki::physics