#include "PhysicsWorld.hpp"

#include <utility>

#include <loki/physics/bodies/PhysicsBody.hpp>
#include <loki/physics/utils/conversions.hpp>

namespace loki::physics {

PhysicsWorld::PhysicsWorld(PhysicsWorldParams&& _params)
    : params(std::move(_params)), world(toB2Vec2(params.gravity)) {}

PhysicsBody PhysicsWorld::createBody(PhysicsBodyParams&& bodyParams) {
  auto bodyDef = bodyParams.toBodyDef();
  auto newBody = world.CreateBody(&bodyDef);
  return PhysicsBody{newBody, this};
}

void PhysicsWorld::update(sf::Time dt) {
  world.Step(dt.asSeconds(), params.velocityIterationCount, params.positionIterationCount);
}

float PhysicsWorld::getPixelsToMetersRatio() const {
  return params.pixelsToMetersRatio;
}

}  // namespace loki::physics
