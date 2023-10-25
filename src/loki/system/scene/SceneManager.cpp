#include "SceneManager.hpp"

#include <fstream>

#include <loki/core/reflection/ReflectionFactory.hpp>
#include <loki/system/app/ServiceRegistry.hpp>

namespace loki::system {

void SceneManager::loadSceneDb(const std::filesystem::path& databaseFile) {
  std::ifstream file(databaseFile);
  core::json json;
  file >> json;
  json.at("scenes").get_to(sceneDb);
  auto databaseParentPath = databaseFile.parent_path();
  for (auto& scenePath : sceneDb) {
    scenePath.second = databaseParentPath / scenePath.second;
  }
}

void SceneManager::startScene(const SceneId& sceneId) {
  std::ifstream file(sceneDb.at(sceneId));
  core::json json;
  file >> json;
  scene = std::make_unique<Scene>();
  json.get_to(*scene);
}

}  // namespace loki::system
