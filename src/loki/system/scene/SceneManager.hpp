#pragma once

#include <filesystem>
#include <map>
#include <string>

#include <nlohmann/json.hpp>

#include <loki/core/json/Path.hpp>
#include <loki/system/ecs/ActorManager.hpp>

#include "Scene.hpp"

namespace loki::system {

using SceneId = std::string;

class SceneManager {
 public:
  explicit SceneManager(ActorManager& actorManager);
  void loadSceneDb(const std::filesystem::path& databaseFile);

  void startScene(const SceneId& sceneId);

 private:
  void instanciateScene(const nlohmann::json& sceneData);

 private:
  ActorManager& actorManager;
  std::map<SceneId, std::filesystem::path> sceneDb;
  std::unique_ptr<Scene> scene;
};

}  // namespace loki::system