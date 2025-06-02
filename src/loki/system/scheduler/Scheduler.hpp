#pragma once

#include <SFML/System/Time.hpp>
#include <rtti/BaseObject.hpp>

#include "UpdateSteps.hpp"

namespace loki::system {
class ApplicationInterface;
class SceneManager;

class Scheduler : public core::BaseObject {
 public:
  explicit Scheduler(ApplicationInterface& app, SceneManager& sceneManager);
  void initGameModules();
  void update(sf::Time dt);

  void setPaused(bool isPaused);
  [[nodiscard]] bool isPaused() const;

 private:
  void handleComponentsLifecycle();
  void runUpdateSteps(sf::Time dt);
  void runUpdateStepForGameModules(sf::Time dt, UpdateStep updateStep);
  void runUpdateStepForComponents(sf::Time dt, UpdateStep updateStep);

 private:
  ApplicationInterface& app;
  SceneManager& sceneManager;
  bool paused = false;

  LOKI_RTTI_CLASS_DECLARE(Scheduler)
};

}  // namespace loki::system

LOKI_REFLECTION_CLASS_BEGIN_RTTI_NO_FACTORY(loki::system::Scheduler)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::system::Scheduler)