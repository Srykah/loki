#include "PhysicsWorldComponent.hpp"

#include "loki/physics/module/PhysicsModule.hpp"

namespace loki::physics {

void PhysicsWorldComponent::onStartInit() {
  world = getService<PhysicsModule>().createWorld(auto{worldParams});
}

void PhysicsWorldComponent::update(sf::Time dt) {
  if (world)
    world->update(dt);
}

PhysicsWorld* PhysicsWorldComponent::getWorld() const {
  return world.get();
}

}  // namespace loki::physics
