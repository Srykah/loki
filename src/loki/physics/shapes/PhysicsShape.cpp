#include "PhysicsShape.hpp"

namespace loki::physics {

PhysicsShape::PhysicsShape(b2Fixture* fixture, PhysicsBody* parentBody) : fixture(fixture), parentBody(parentBody) {}

PhysicsShapeType PhysicsShape::getShapeType() const {
  return static_cast<PhysicsShapeType>(fixture->GetType());
}
}  // namespace loki::physics
