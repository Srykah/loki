#include "PhysicsBody.hpp"

#include <numbers>

#include <loki/physics/shapes/PhysicsShape.hpp>
#include <loki/physics/utils/conversions.hpp>
#include <loki/physics/world/PhysicsWorld.hpp>

namespace loki::physics {
PhysicsBody::PhysicsBody(b2Body* body, PhysicsWorld* parentWorld) : parentWorld(parentWorld), body(body) {}

void PhysicsBody::createFixture(PhysicsFixtureParams&& shapeParams) {
  auto fixtureDef = shapeParams.toFixtureDef();
  body->CreateFixture(&fixtureDef);
}

sf::Vector2f PhysicsBody::getPosition() const {
  return toSfVec2(body->GetPosition()) * parentWorld->getPixelsToMetersRatio();
}

float PhysicsBody::getRotationInDegrees() const {
  return body->GetAngle() * 180.f * std::numbers::inv_pi;
}

}  // namespace loki::physics
