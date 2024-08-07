#pragma once

#include <SFML/System/Time.hpp>

#include "UpdateSteps.hpp"

namespace loki::system {
class ApplicationInterface;
class SceneManager;

class Scheduler {
 public:
  explicit Scheduler(ApplicationInterface& app, SceneManager& sceneManager);
  void initGameModules();
  void update(sf::Time dt);

 private:
  void handleComponentsLifecycle();
  void runUpdateSteps(sf::Time dt);
  void runUpdateStepForGameModules(sf::Time dt, UpdateStep updateStep);
  void runUpdateStepForComponents(sf::Time dt, UpdateStep updateStep);

 private:
  ApplicationInterface& app;
  SceneManager& sceneManager;
};

}  // namespace loki::system