#include "SceneManager.hpp"

#include <fstream>

namespace loki::system {

SceneManager::SceneManager(ActorManager& actorManager) : actorManager(actorManager) {}

void SceneManager::loadSceneDb(const std::filesystem::path& databaseFile) {
  std::ifstream file(databaseFile);
  nlohmann::json json;
  file >> json;
  json.at("scenes").get_to(sceneDb);
}

void SceneManager::startScene(const SceneId& sceneId) {
  std::ifstream file(sceneDb.at(sceneId));
  nlohmann::json json;
  file >> json;
  instanciateScene(json);
}

void SceneManager::instanciateScene(const nlohmann::json& sceneData) {
  auto newScene = std::make_unique<Scene>();
  // newScene->root = actorManager.instanciateActor(sceneData.at("root"));
  scene = std::move(newScene);
}

}  // namespace loki::system
