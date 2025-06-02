#include "SceneManager.hpp"

#include <fstream>

#include <loki/core/serialization/yaml/fromYaml.hpp>
#include <loki/system/window/Window.hpp>

namespace loki::system {

Scene* SceneManager::getCurrentScene() const {
  return currentScene;
}

void SceneManager::setScenePaths(ScenePaths&& _scenePaths) {
  scenePaths = std::move(_scenePaths);
}

const SceneManager::ScenePaths& SceneManager::getScenePaths() const {
  return scenePaths;
}

Scene* SceneManager::loadScene(const std::string& sceneName, bool setActive) {
  const auto& scenePath = scenePaths.at(sceneName);
  Scene* newScene = loadSceneFromYamlFile(scenePath);
  newScene->setPath(scenePath);
  if (setActive) {
    // unload currentScene
    currentScene = newScene;
  }
  return newScene;
}

Scene* SceneManager::loadSceneFromYaml(const YAML::Node& sceneNode) {
  auto newScene = std::make_unique<Scene>();
  newScene->loadFromYaml(sceneNode);
  return scenes.emplace_back(std::move(newScene)).get();
}

Scene* SceneManager::loadSceneFromYamlString(const std::string& sceneData) {
  YAML::Node sceneNode = YAML::Load(sceneData);
  return loadSceneFromYaml(sceneNode);
}

Scene* SceneManager::loadSceneFromYamlFile(const std::filesystem::path& scenePath) {
  std::ifstream sceneData{scenePath};
  YAML::Node sceneNode = YAML::Load(sceneData);
  return loadSceneFromYaml(sceneNode);
}

}  // namespace loki::system