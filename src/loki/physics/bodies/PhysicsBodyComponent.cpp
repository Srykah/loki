#include "PhysicsBodyComponent.hpp"

#include <loki/system/scene/SceneManager.hpp>
#include <loki/physics/world/PhysicsWorldComponent.hpp>

namespace loki::physics {

void PhysicsBodyComponent::onStartInit() {
  body = getScene().getRoot().getComponent<PhysicsWorldComponent>()->getWorld()->createBody(auto{bodyParams});
  for (const auto& fixtureParam : fixtureParams) {
    body.createFixture(auto{fixtureParam});
  }
}

void PhysicsBodyComponent::onFinalizeInit() {
  body.setTransformable(getActor().getTransformable());  // init position and rotation
}

void PhysicsBodyComponent::onPrePhysics(sf::Time dt) {
  body.setTransformable(getActor().getTransformable());
}

void PhysicsBodyComponent::onPhysicsResult(sf::Time dt) {
  auto transformable = getActor().getTransformable();
  transformable.setPosition(body.getPosition());
  transformable.setRotation(body.getRotationInDegrees());
  getActor().setTransformable(std::move(transformable));
}

}  // namespace loki::physics
