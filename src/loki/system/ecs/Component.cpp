#include "Component.hpp"

#include <loki/system/ecs/Actor.hpp>

namespace loki::system {

Actor Component::getActor() const {
  return actor;
}

Scene& Component::getScene() const {
  return actor.getScene();
}

const sf::Transform& Component::getLocalTransform() const {
  return getActor().getLocalTransform();
}

sf::Transform Component::getGlobalTransform() const {
  return getActor().getGlobalTransform();
}

void Component::setActor(Actor _actor) {
  actor = _actor;
}

}  // namespace loki::system
