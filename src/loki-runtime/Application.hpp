#pragma once

#include <dylib/dylib.hpp>

#include <loki/core/runtimeObject/RuntimeObjectRegistry.hpp>
#include <loki/core/services/ServiceRegistry.hpp>
#include <loki/system/ecs/ComponentRegistry.hpp>
#include <loki/system/modules/GameModule.hpp>
#include <loki/system/res/ResourceHolder.hpp>
#include <loki/system/scene/SceneManager.hpp>
#include <loki/system/window/Window.hpp>

namespace loki::app {
class Application {
 public:
  void run();

 private:
  void init();
  void registerServices();
  void loadGame(const std::filesystem::path& path);
  void loop();

 private:
  std::unique_ptr<dylib> gameScriptsLibrary;  // keep it at the top (the library must outlive the registries)
  core::RuntimeObjectRegistry runtimeObjectRegistry;
  system::ComponentRegistry componentRegistry;
  system::ServiceRegistry serviceRegistry;
  system::ResourceHolder resourceHolder;
  system::SceneManager sceneManager;
  system::Window window;
  std::vector<std::unique_ptr<system::GameModule>> gameModules;
};

}  // namespace loki::app
