#include "Component.hpp"

#include "Actor.hpp"

namespace loki::system {

Actor& Component::getActor() const {
  assert(actor);
  return *actor;
}

const sf::Transform& Component::getTransform() const {
  return getActor().getTransform();
}

void Component::setActor(Actor& _actor) {
  actor = &_actor;
}

}  // namespace loki::system
