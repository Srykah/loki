#include "ActorManager.hpp"

#include <filesystem>
#include <fstream>

#include <loki/core/json/Path.hpp>

#include "Actor.hpp"

namespace loki::system {

core::BorrowerPtr<Actor> ActorManager::instanciateActor(const nlohmann::json& actorData, Actor* parent) {
  actors.emplace_back(new Actor(registry, parent));
  nlohmann::json fullActorData = loadOverrides(actorData);

  return actors.back().borrow();
}

void ActorManager::update(sf::Time delta) {
  for (auto&& [prio, groupsInPrio] : groups) {
    for (auto& group : groupsInPrio) {
      group->update(delta);
    }
  }
}

nlohmann::json ActorManager::loadOverrides(const nlohmann::json& partialData) {
  nlohmann::json fullData;
  for (const auto& prefab : partialData["prefabs"]) {
    std::filesystem::path prefabPath;
    prefab.at("path").get_to(prefabPath);
    std::ifstream prefabFile(prefabPath);
    nlohmann::json prefabData;
    prefabFile >> prefabData;
    const nlohmann::json& prefabPatch = prefab.at("patch");
    prefabData.patch(prefabData);
    fullData.merge_patch(prefabData);
  }
  return fullData;
}

}  // namespace loki::system
