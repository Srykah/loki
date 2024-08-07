#include "PhysicsWorldComponent.hpp"

namespace loki::physics {

void PhysicsWorldComponent::onStartInit() {
  world = std::make_unique<PhysicsWorld>(auto{worldParams});
}

void PhysicsWorldComponent::update(sf::Time dt, UpdateSteps::PhysicsSimulation) {
  if (world)
    world->update(dt);
}

PhysicsWorld* PhysicsWorldComponent::getWorld() const {
  return world.get();
}

}  // namespace loki::physics
