#include "ComponentRegistry.hpp"

#include "Actor.hpp"
#include "Component.hpp"

namespace loki::system {

const BaseComponentTraits* ComponentRegistry::getTraits(const entt::type_info& type) const {
  if (auto it = componentTraits.find(type); it != componentTraits.end())
    return it->second.get();
  return nullptr;
}

void* ComponentRegistry::addComponentToActor(Actor& actor, const std::string& compName) const {
  Component& comp = componentFactories.at(compName)(actor.handle);
  comp.setActor(actor);
  return static_cast<void*>(&comp);
}

}  // namespace loki::system
