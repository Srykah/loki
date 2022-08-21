#include "ActorManager.hpp"
#include <ranges>

namespace loki::system {

void ActorManager::update(sf::Time delta) {
  for (auto&& [priority, updaterList] : updaters) {
    for (const auto& updater : updaterList) {
      updater();
    }
  }
}

}  // namespace loki::system