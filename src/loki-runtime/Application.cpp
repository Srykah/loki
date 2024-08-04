#include "Application.hpp"

#include <fstream>

#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>
#include <dylib/dylib.hpp>
#include <yaml-cpp/node/parse.h>

#include <loki/core/reflection/basicTypesInfo.hpp>
#include <loki/core/serialization/yaml/fromYaml.hpp>

#include "registerLokiTypes.hpp"

namespace {
const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
}

namespace loki::app {

void Application::run() {
  init();
  loop();
}

std::span<std::unique_ptr<system::GameModule>> Application::getGameModules() {
  return gameModules;
}

void Application::exit() {
  isRunning = false;
}

void Application::init() {
  registerLokiRuntimeTypes(runtimeObjectRegistry);
  registerLokiModules(runtimeObjectRegistry);
  registerLokiComponents(runtimeObjectRegistry, componentRegistry);
  registerServices();
  loadGame("data/game.yml");
}

void Application::registerServices() {
  serviceRegistry.registerService(runtimeObjectRegistry);
  serviceRegistry.registerService(componentRegistry);
  serviceRegistry.registerService(resourceHolder);
  serviceRegistry.registerService(sceneManager);
  serviceRegistry.registerService<ApplicationInterface>(*this);
}

void Application::loadGame(const std::filesystem::path& path) {
  std::ifstream file{path};
  YAML::Node node = YAML::Load(file);

  auto gameScripts = node["gameScripts"].as<std::string>();
  gameScriptsLibrary = std::make_unique<dylib>("./", gameScripts);
  void* serviceRegistryAsVoidPtr = &serviceRegistry;
  void* runtimeObjectRegistryAsVoidPtr = &runtimeObjectRegistry;
  void* componentRegistryAsVoidPtr = &componentRegistry;
  gameScriptsLibrary->get_function<void(const void*)>("registerServiceRegistry")(serviceRegistryAsVoidPtr);
  gameScriptsLibrary->get_function<void(void*)>("registerCustomRuntimeTypes")(runtimeObjectRegistryAsVoidPtr);
  gameScriptsLibrary->get_function<void(void*)>("registerCustomModules")(runtimeObjectRegistryAsVoidPtr);
  gameScriptsLibrary->get_function<void(void*, void*)>("registerCustomComponents")(runtimeObjectRegistryAsVoidPtr,
                                                                                   componentRegistryAsVoidPtr);

  core::fromYaml(node["gameModules"], gameModules);
  for (const auto& gameModule : gameModules)
    gameModule->registerAsAService(serviceRegistry);

  std::map<std::string, std::filesystem::path> scenePaths;
  core::fromYaml(node["scenePaths"], scenePaths);
  sceneManager.setScenePaths(std::move(scenePaths));

  sceneManager.loadScene(node["firstSceneName"].as<std::string>());
  scheduler.init();
}

void Application::loop() {
  sf::Clock clock;
  sf::Time timeSinceLastFrame;
  while (isRunning) {
    timeSinceLastFrame += clock.restart();
    for (; timeSinceLastFrame >= TIME_PER_FRAME; timeSinceLastFrame -= TIME_PER_FRAME) {
      resourceHolder.load();
      scheduler.update(TIME_PER_FRAME);
    }
    sf::sleep((TIME_PER_FRAME - timeSinceLastFrame) / 2.f);
  }
}

}  // namespace loki::app
