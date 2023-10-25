#include "ActorManager.hpp"

#include <filesystem>
#include <fstream>

#include <loki/core/json/Path.hpp>

#include "Actor.hpp"

namespace loki::system {

core::BorrowerPtr<Actor> ActorManager::instanciateActor(const core::json& actorData, Actor* parent) {
  actors.emplace_back(new Actor(registry, parent));
  core::json fullActorData = loadOverrides(actorData);

  return actors.back().borrow();
}

void ActorManager::update(sf::Time delta) {
  for (auto&& [prio, groupsInPrio] : groups) {
    for (auto& group : groupsInPrio) {
      group->update(delta);
    }
  }
}

core::json ActorManager::loadOverrides(const core::json& partialData) {
  core::json fullData;
  for (const auto& prefab : partialData["prefabs"]) {
    std::filesystem::path prefabPath;
    prefab.at("path").get_to(prefabPath);
    std::ifstream prefabFile(prefabPath);
    core::json prefabData;
    prefabFile >> prefabData;
    const core::json& prefabPatch = prefab.at("patch");
    prefabData.patch(prefabData);
    fullData.merge_patch(prefabData);
  }
  return fullData;
}

}  // namespace loki::system
