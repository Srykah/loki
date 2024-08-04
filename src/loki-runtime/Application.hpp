#pragma once

#include <dylib/dylib.hpp>

#include <loki/core/rtti/RuntimeObjectRegistry.hpp>
#include <loki/core/services/ServiceRegistry.hpp>
#include <loki/system/app/ApplicationInterface.hpp>
#include <loki/system/ecs/ComponentRegistry.hpp>
#include <loki/system/modules/GameModule.hpp>
#include <loki/system/res/ResourceHolder.hpp>
#include <loki/system/scene/SceneManager.hpp>
#include <loki/system/scheduler/Scheduler.hpp>

namespace loki::app {
class Application final : public system::ApplicationInterface {
 public:
  void run();
  std::span<std::unique_ptr<system::GameModule>> getGameModules() override;
  void exit() override;

 private:
  void init();
  void registerServices();
  void loadGame(const std::filesystem::path& path);
  void loop();

 private:
  std::unique_ptr<dylib> gameScriptsLibrary;  // keep it at the top (the library must outlive the registries)
  core::RuntimeObjectRegistry runtimeObjectRegistry;
  core::ServiceRegistry serviceRegistry;
  system::ComponentRegistry componentRegistry;
  system::ResourceHolder resourceHolder;
  system::SceneManager sceneManager;
  system::Scheduler scheduler{*this, sceneManager};
  std::vector<std::unique_ptr<system::GameModule>> gameModules;
  bool isRunning = true;
};

}  // namespace loki::app
