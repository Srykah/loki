#include "PhysicsShape.hpp"

#include <loki/physics/bodies/PhysicsBody.hpp>
#include <loki/physics/world/PhysicsWorld.hpp>

namespace loki::physics {

PhysicsShape::PhysicsShape(PhysicsBody* parentBody, const PhysicsShapeParams& shapeParams, const sf::Transformable& trs)
    : parentBody(parentBody) {
  shapeId = shapeParams.createShape(parentBody->getBodyId(), trs);
}

void PhysicsShape::clear(){
  parentBody = nullptr;
  shapeId = b2_nullShapeId;
  isChain = false;
}

PhysicsShape::PhysicsShape(PhysicsShape&& _other) noexcept
    : parentBody(_other.parentBody), shapeId(_other.shapeId), isChain(_other.isChain) {
  _other.clear();
}

PhysicsShape& PhysicsShape::operator=(PhysicsShape&& _other) noexcept {
  destroy(true);
  parentBody = _other.parentBody;
  shapeId = _other.shapeId;
  isChain = _other.isChain;
  _other.clear();
  return *this;
}

PhysicsShape::~PhysicsShape() {
  destroy(true);
}

void PhysicsShape::destroy(bool updateBodyMass) {
  if (parentBody == nullptr || B2_ID_EQUALS(shapeId, b2_nullShapeId)) {
    return;
  }
  if (isChain) {
    b2DestroyChain(reinterpret_cast<const b2ChainId&>(shapeId));
  } else {
    b2DestroyShape(shapeId, updateBodyMass);
  }
  clear();
}

PhysicsShapeType PhysicsShape::getShapeType() const {
  return static_cast<PhysicsShapeType>(b2Shape_GetType(shapeId));
}

}  // namespace loki::physics
