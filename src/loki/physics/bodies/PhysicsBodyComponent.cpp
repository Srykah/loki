#include "PhysicsBodyComponent.hpp"

#include <loki/system/scene/SceneManager.hpp>
#include <loki/physics/world/PhysicsWorldComponent.hpp>

namespace loki::physics {

void PhysicsBodyComponent::onStartInit() {
  body = getService<system::SceneManager>()
             .getCurrentScene()
             ->getRoot()
             .getComponent<PhysicsWorldComponent>()
             ->getWorld()
             ->createBody(auto{bodyParams});
  for (const auto& fixtureParams : bodyParams.fixtureParams) {
    body.createFixture(auto{fixtureParams});
  }
}

void PhysicsBodyComponent::update(sf::Time dt) {
  auto transformable = getActor().getTransformable();
  transformable.setPosition(body.getPosition());
  transformable.setRotation(body.getRotationInDegrees());
  getActor().setTransformable(std::move(transformable));
}

}  // namespace loki::physics
