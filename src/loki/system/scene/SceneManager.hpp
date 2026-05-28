#pragma once

#include <filesystem>
#include <map>

#include <ryml.hpp>

#include <loki/core/reflection/classMacros.hpp>
#include <loki/core/rtti/BaseObject.hpp>
#include <loki/system/scene/Scene.hpp>

namespace loki::system {
class Window;

class SceneManager : public core::BaseObject {
 public:
  using ScenePaths = std::map<std::string, std::filesystem::path>;

 public:
  Scene* getCurrentScene() const;

  void setScenePaths(ScenePaths&& scenePaths);
  const ScenePaths& getScenePaths() const;
  Scene* loadScene(const std::string& sceneName, bool setActive = true);

 private:
  Scene* loadSceneFromYaml(const ryml::ConstNodeRef& sceneNode);
  Scene* loadSceneFromYamlString(const std::string& sceneData);
  Scene* loadSceneFromYamlFile(const std::filesystem::path& scenePath);

 private:
  ScenePaths scenePaths;
  Scene* currentScene = nullptr;
  Scene* nextScene = nullptr;
  std::vector<std::unique_ptr<Scene>> scenes;

  LOKI_RTTI_CLASS_DECLARE(SceneManager)
};
}  // namespace loki::system

LOKI_REFLECTION_CLASS_BEGIN_RTTI(loki::system::SceneManager)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::system::SceneManager)