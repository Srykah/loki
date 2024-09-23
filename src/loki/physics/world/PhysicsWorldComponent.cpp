#include "PhysicsWorldComponent.hpp"

namespace loki::physics {

void PhysicsWorldComponent::onStartInit() {
  world = std::make_unique<PhysicsWorld>(auto{worldParams});
}

void PhysicsWorldComponent::onPhysicsSimulation(sf::Time delta) {
  if (world)
    world->update(delta);
}

PhysicsWorld* PhysicsWorldComponent::getWorld() const {
  return world.get();
}

}  // namespace loki::physics
