#include "PhysicsShape.hpp"

#include <loki/physics/bodies/PhysicsBody.hpp>
#include <loki/physics/world/PhysicsWorld.hpp>

namespace loki::physics {

PhysicsShape::PhysicsShape(PhysicsBody* parentBody, const PhysicsShapeParams& shapeParams, const sf::Transformable& trs)
    : parentBody(parentBody) {
  shapeId = shapeParams.createShape(parentBody->getBodyId(), trs);
}

PhysicsShape::~PhysicsShape() {

}

PhysicsShapeType PhysicsShape::getShapeType() const {
  return static_cast<PhysicsShapeType>(b2Shape_GetType(shapeId));
}

}  // namespace loki::physics
