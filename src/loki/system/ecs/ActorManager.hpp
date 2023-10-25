#pragma once

#include <functional>
#include <map>

#include <SFML/System/Time.hpp>
#include <entt/entity/registry.hpp>
#include <nlohmann/json.hpp>

#include <loki/core/utils/Memory.hpp>

#include "ComponentGroup.hpp"

namespace loki::system {

class Actor;

class ActorManager {
 public:
  template <class Comp>
  void registerComponent(int priority = 0);

  core::BorrowerPtr<Actor> instanciateActor(const core::json& actorData, Actor* parent = nullptr);

  void update(sf::Time delta);

 private:
  static core::json loadOverrides(const core::json& partialData);

  std::vector<core::OwnerPtr<Actor>> actors;
  entt::registry registry;
  std::map<int, std::vector<std::unique_ptr<ComponentGroupBase>>> groups;
};

template <class Comp>
void ActorManager::registerComponent(int priority) {
  groups[priority].emplace_back(registry);
}

}  // namespace loki::system
