#include "SceneManager.hpp"

#include <fstream>

#include <loki/core/serialization/yaml/fromYaml.hpp>
#include <loki/core/services/ServiceRegistry.hpp>
#include <loki/system/ecs/Actor.hpp>
#include <loki/system/ecs/ComponentRegistry.hpp>
#include <loki/system/window/Window.hpp>

namespace loki::system {

Scene* SceneManager::getCurrentScene() const {
  return scene.get();
}

void SceneManager::loadSceneFromYaml(const YAML::Node& sceneNode) {
  auto newScene = std::make_unique<Scene>();
  getService<ComponentRegistry>().setRegistry(newScene->registry);
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

void SceneManager::update(sf::Time dt) {
  scene->update(dt);
}

void SceneManager::draw(Window& window) const {
  window.draw(*scene);
}

}  // namespace loki::system