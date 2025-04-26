#pragma once

#include <filesystem>
#include <map>

#include <loki/core/reflection/classMacros.hpp>
#include <loki/core/rtti/BaseObject.hpp>
#include <loki/system/scene/Scene.hpp>

namespace YAML {
class Node;
}

namespace loki::system {
class Window;

class SceneManager : public core::BaseObject {
 public:
  using ScenePaths = std::map<std::string, std::filesystem::path>;

 public:
  Scene* getCurrentScene() const;

  void setScenePaths(ScenePaths&& scenePaths);
  const ScenePaths& getScenePaths() const;
  void loadScene(const std::string& sceneName);

 private:
  void loadSceneFromYaml(const YAML::Node& sceneNode);
  void loadSceneFromYamlString(const std::string& sceneData);
  void loadSceneFromYamlFile(const std::filesystem::path& scenePath);

 private:
  ScenePaths scenePaths;
  std::unique_ptr<Scene> scene;

  LOKI_RTTI_CLASS_DECLARE(SceneManager)
};
}  // namespace loki::system

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::core::BaseObject, loki::system::SceneManager)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::system::SceneManager)