#include "PhysicsBody.hpp"

#include <loki/physics/shapes/PhysicsShape.hpp>
#include <loki/physics/utils/conversions.hpp>
#include <loki/physics/world/PhysicsWorld.hpp>

#include "loki/core/math/Misc.hpp"
#include "loki/physics/debug/DrawShapes.hpp"

namespace loki::physics {
PhysicsBody::PhysicsBody(const PhysicsBodyParams& bodyParams, PhysicsWorld* parentWorld) : parentWorld(parentWorld) {
  const auto bodyDef = bodyParams.toBodyDef();
  bodyId = b2CreateBody(parentWorld->getWorldId(), &bodyDef);
}

void PhysicsBody::clear() {
  parentWorld = nullptr;
  bodyId = b2_nullBodyId;
  for (auto& shape : shapes) {
    shape.clear();
  }
  shapes.clear();
}

PhysicsBody::PhysicsBody(PhysicsBody&& _other) noexcept
    : parentWorld(_other.parentWorld), bodyId(_other.bodyId), shapes(std::move(_other.shapes)) {
  _other.clear();
}

PhysicsBody& PhysicsBody::operator=(PhysicsBody&& _other) noexcept {
  destroy();
  parentWorld = _other.parentWorld;
  bodyId = _other.bodyId;
  shapes = std::move(_other.shapes);
  _other.clear();
  return *this;
}

PhysicsBody::~PhysicsBody() {
  destroy();
}

void PhysicsBody::destroy() {
  if (parentWorld == nullptr || B2_ID_EQUALS(bodyId, b2_nullBodyId)) {
    return;
  }
  b2DestroyBody(bodyId);
  clear();
}

PhysicsShape& PhysicsBody::createShape(const PhysicsShapeParams& shapeParams, const sf::Transformable& trs) {
  shapes.push_back(PhysicsShape{this, shapeParams, trs});
  return shapes.back();
}

void PhysicsBody::setTransformable(const sf::Transformable& transformable) {
  b2Body_SetTransform(bodyId, toB2Vec2(transformable.getPosition() / parentWorld->getPixelsToMetersRatio()),
                      b2MakeRot(transformable.getRotation().asRadians()));
}

sf::Vector2f PhysicsBody::getPosition() const {
  return toSfVec2(b2Body_GetTransform(bodyId).p) * parentWorld->getPixelsToMetersRatio();
}

sf::Angle PhysicsBody::getRotation() const {
  return sf::radians(b2Rot_GetAngle(b2Body_GetTransform(bodyId).q));
}

void PhysicsBody::applyForce(const sf::Vector2f& force) {
  b2Body_ApplyForceToCenter(bodyId, toB2Vec2(force), true);
}

void PhysicsBody::applyLinearImpulse(const sf::Vector2f& linearImpulse) {
  b2Body_ApplyLinearImpulseToCenter(bodyId, toB2Vec2(linearImpulse), true);
}

sf::FloatRect PhysicsBody::getBoundingBox() const {
  return toSfAABB(b2Body_ComputeAABB(bodyId));

#if 0
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

#endif
}

#if 0
void PhysicsBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform.scale(parentWorld->getPixelsToMetersRatio(), parentWorld->getPixelsToMetersRatio());
  const auto bodyTrs = b2Body_GetTransform(bodyId);
  states.transform.translate(toSfVec2(bodyTrs.p));
  states.transform.rotate(core::toDegrees(b2Rot_GetAngle(bodyTrs.q)));
  for (const auto& shape : shapes) {
    target.draw(shape, states);
  }
}
#endif

}  // namespace loki::physics
