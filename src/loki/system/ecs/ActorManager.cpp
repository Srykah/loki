#include "ActorManager.hpp"

#include <ranges>

namespace loki::system {

void ActorManager::update(sf::Time delta) {
  for (auto&& [prio, groupsInPrio] : groups) {
    for (auto& group : groupsInPrio) {
      group->update(delta);
    }
  }
}

}  // namespace loki::system