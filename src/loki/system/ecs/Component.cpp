#include "Component.hpp"

#include "Actor.hpp"

namespace loki::system {

Actor Component::getActor() const {
  return actor;
}

const sf::Transform& Component::getLocalTransform() const {
  return getActor().getLocalTransform();
}

sf::Transform Component::getGlobalTransform() const {
  return getActor().getGlobalTransform();
}

Component::Status Component::getStatus() const {
  return status;
}

void Component::startInit() {
  onStartInit();
  if (status != Status::LOADING_RESOURCES)
    status = Status::RESOURCES_LOADED;
}

void Component::finalizeInit() {
  onFinalizeInit();
  status = Status::READY;
}

void Component::setActor(Actor _actor) {
  actor = _actor;
}

void Component::onResourcesLoaded() {
  status = Status::RESOURCES_LOADED;
}

}  // namespace loki::system
