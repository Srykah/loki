#include "ComponentRegistry.hpp"

#include "Actor.hpp"
#include "Component.hpp"

namespace loki::system {

void ComponentRegistry::setRegistry(entt::registry& _registry) {
  registry = &_registry;
  reconnectObservers();
}

void ComponentRegistry::reconnectObservers() {
  assert(registry);
  for (auto&& [_, initData] : initSteps) {
    initData.observerConnector(initData.observer, *registry);
  }
}

void* ComponentRegistry::addComponentToActor(Actor& actor, const std::string& compName) const {
  Component& comp = componentFactories.at(compName)(actor.handle);
  comp.setActor(actor);
  return static_cast<void*>(&comp);
}

}  // namespace loki::system
