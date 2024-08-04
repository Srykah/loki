#include "PhysicsWorldComponent.hpp"

namespace loki::physics {

void PhysicsWorldComponent::onStartInit() {
  world = std::make_unique<PhysicsWorld>(auto{worldParams});
}

void PhysicsWorldComponent::update(system::UpdateStep updateStep, sf::Time dt) {
  if (world)
    world->update(dt);
}

PhysicsWorld* PhysicsWorldComponent::getWorld() const {
  return world.get();
}

}  // namespace loki::physics
