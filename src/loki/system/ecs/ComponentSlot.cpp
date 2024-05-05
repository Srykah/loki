#if 0

#include "ComponentSlot.hpp"

#include "Actor.hpp"

namespace loki::system {

ComponentSlot::ComponentSlot(Actor& actor) : actor(actor) {
  index = actor.components.size();
  actor.components.emplace_back(nullptr);
}

Component*& ComponentSlot::get() {
  return actor.components[index];
}

const Component* ComponentSlot::get() const {
  return actor.components[index];
}

void ComponentSlot::destroy() {
  get()->destroy();
  actor.components.erase(actor.components.begin() + index);
}

}

#endif