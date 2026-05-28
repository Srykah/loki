#include "PhysicsWorld.hpp"

#include <utility>

#include <loki/physics/bodies/PhysicsBody.hpp>
#include <loki/physics/utils/conversions.hpp>

namespace loki::physics {

PhysicsWorld::PhysicsWorld(PhysicsWorldParams&& _params) : params(std::move(_params)) {
  b2WorldDef worldDef = b2DefaultWorldDef();
  worldDef.gravity = toB2Vec2(params.gravity);
  worldId = b2CreateWorld(&worldDef);
}

PhysicsWorld::~PhysicsWorld() {
  b2DestroyWorld(worldId);
  worldId = b2_nullWorldId;
}

PhysicsBody PhysicsWorld::createBody(PhysicsBodyParams&& bodyParams) {
  return PhysicsBody{std::move(bodyParams), this};
}

void PhysicsWorld::update(sf::Time dt) {
  b2World_Step(worldId, dt.asSeconds(), params.subStepCount);
}

float PhysicsWorld::getPixelsToMetersRatio() const {
  return params.pixelsToMetersRatio;
}

}  // namespace loki::physics
