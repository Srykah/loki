#pragma once

#include <filesystem>
#include <map>

#include <SFML/System/Time.hpp>

#include <loki/system/scene/Scene.hpp>

namespace YAML {
class Node;
}

namespace loki::system {
class Window;

class SceneManager : public core::BaseObject {
 public:
  Scene* getCurrentScene() const;

  void setScenePaths(std::map<std::string, std::filesystem::path>&& scenePaths);
  void loadScene(const std::string& sceneName);

  void update(sf::Time dt);
  void draw(Window& window) const;

 private:
  void loadSceneFromYaml(const YAML::Node& sceneNode);
  void loadSceneFromYamlString(const std::string& sceneData);
  void loadSceneFromYamlFile(const std::filesystem::path& scenePath);

 private:
  std::map<std::string, std::filesystem::path> scenePaths;
  std::unique_ptr<Scene> scene;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(SceneManager)
};
}  // namespace loki::system

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::core::BaseObject, loki::system::SceneManager)
LOKI_REFLECTION_CLASS_END_RTTI(loki::system::SceneManager)