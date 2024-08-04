#include "SceneManager.hpp"

#include <fstream>

#include <loki/core/serialization/yaml/fromYaml.hpp>
#include <loki/system/window/Window.hpp>

namespace loki::system {

Scene* SceneManager::getCurrentScene() const {
  return scene.get();
}

void SceneManager::setScenePaths(std::map<std::string, std::filesystem::path>&& _scenePaths) {
  scenePaths = std::move(_scenePaths);
}

void SceneManager::loadScene(const std::string& sceneName) {
  loadSceneFromYamlFile(scenePaths.at(sceneName));
}

void SceneManager::loadSceneFromYaml(const YAML::Node& sceneNode) {
  auto newScene = std::make_unique<Scene>();
  newScene->loadFromYaml(sceneNode);
  scene = std::move(newScene);
}

void SceneManager::loadSceneFromYamlString(const std::string& sceneData) {
  YAML::Node sceneNode = YAML::Load(sceneData);
  loadSceneFromYaml(sceneNode);
}

void SceneManager::loadSceneFromYamlFile(const std::filesystem::path& scenePath) {
  std::ifstream sceneData{scenePath};
  YAML::Node sceneNode = YAML::Load(sceneData);
  loadSceneFromYaml(sceneNode);
}

}  // namespace loki::system