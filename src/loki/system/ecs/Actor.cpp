#include "Actor.hpp"

namespace loki::system {

Actor::Actor(entt::registry& registry, Actor* parent) : SceneNode(parent), id(registry.create()), registry(registry) {}

Actor* Actor::getParentActor() const {
  if (isRoot)
    return nullptr;
  return static_cast<Actor*>(parent);
}

}  // namespace loki::system
