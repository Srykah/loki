#include "PhysicsBody.hpp"

#include <loki/physics/shapes/PhysicsShape.hpp>
#include <loki/physics/utils/conversions.hpp>
#include <loki/physics/world/PhysicsWorld.hpp>

#include "loki/core/math/Misc.hpp"
#include "loki/physics/debug/DrawShapes.hpp"

namespace loki::physics {
PhysicsBody::PhysicsBody(b2Body* body, PhysicsWorld* parentWorld) : parentWorld(parentWorld), body(body) {}

void PhysicsBody::createFixture(PhysicsFixtureParams&& shapeParams) {
  auto fixtureDef = shapeParams.toFixtureDef();
  body->CreateFixture(&fixtureDef);
}

void PhysicsBody::setTransformable(const sf::Transformable& transformable) {
  body->SetTransform(toB2Vec2(transformable.getPosition() / parentWorld->getPixelsToMetersRatio()),
                     core::toRadians(transformable.getRotation()));
}

sf::Vector2f PhysicsBody::getPosition() const {
  return toSfVec2(body->GetPosition()) * parentWorld->getPixelsToMetersRatio();
}

float PhysicsBody::getRotationInDegrees() const {
  return core::toDegrees(body->GetAngle());
}

void PhysicsBody::applyForce(const sf::Vector2f& force) {
  body->ApplyForceToCenter(toB2Vec2(force), true);
}

void PhysicsBody::applyLinearImpulse(const sf::Vector2f& linearImpulse) {
  body->ApplyLinearImpulseToCenter(toB2Vec2(linearImpulse), true);
}

void PhysicsBody::debugDraw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform.scale(parentWorld->getPixelsToMetersRatio(), parentWorld->getPixelsToMetersRatio());
  states.transform.translate(toSfVec2(body->GetPosition()));
  states.transform.rotate(core::toDegrees(body->GetAngle()));
  for (const auto* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
    debug::drawShape(target, *fixture->GetShape(), states);
}

}  // namespace loki::physics
