#include "PhysicsShape.hpp"

#include <loki/physics/bodies/PhysicsBody.hpp>

namespace loki::physics {

PhysicsShape::PhysicsShape(const PhysicsShapeParams& shapeParams, PhysicsBody* parentBody) : parentBody(parentBody) {
  shapeId = shapeParams.createShape(parentBody->getBodyId());
}

PhysicsShape::~PhysicsShape() {

}

PhysicsShapeType PhysicsShape::getShapeType() const {
  return static_cast<PhysicsShapeType>(b2Shape_GetType(shapeId));
}
}  // namespace loki::physics
