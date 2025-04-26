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

sf::FloatRect PhysicsBody::getBoundingBox() const {
  if (!body)
    return {};

#define LOKI_PHYSICS_BODY_BV_ALT 1

  b2AABB aabb;
  b2Transform trs;
  trs.SetIdentity();
  aabb.lowerBound = b2Vec2{FLT_MAX, FLT_MAX};
  aabb.upperBound = b2Vec2{-FLT_MAX, -FLT_MAX};

  for (const auto* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext()) {
    const b2Shape* shape = fixture->GetShape();
    const int32 childCount = shape->GetChildCount();
    for (int32 child = 0; child < childCount; ++child) {
#if LOKI_PHYSICS_BODY_BV_ALT == 1
      b2AABB shapeAABB;
      shape->ComputeAABB(&shapeAABB, trs, child);
      aabb.Combine(shapeAABB);
#elif LOKI_PHYSICS_BODY_BV_ALT == 2
      aabb.Combine(fixture->GetAABB(child));
#endif
    }
  }

  if (!aabb.IsValid())
    return {};

  auto pos = toSfVec2(aabb.lowerBound);
  auto size = toSfVec2(aabb.upperBound) - pos;
#if LOKI_PHYSICS_BODY_BV_ALT == 1
  return sf::FloatRect{pos, size * parentWorld->getPixelsToMetersRatio()};
#elif LOKI_PHYSICS_BODY_BV_ALT == 2
  return sf::FloatRect{pos, size * parentWorld->getPixelsToMetersRatio()};
#endif
}

void PhysicsBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform.scale(parentWorld->getPixelsToMetersRatio(), parentWorld->getPixelsToMetersRatio());
  states.transform.translate(toSfVec2(body->GetPosition()));
  states.transform.rotate(core::toDegrees(body->GetAngle()));
  for (const auto* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
    debug::drawShape(target, *fixture->GetShape(), states);
}

}  // namespace loki::physics
