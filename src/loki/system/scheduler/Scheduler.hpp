#pragma once

#include <SFML/System/Time.hpp>

namespace loki::system {
class ApplicationInterface;
class SceneManager;

class Scheduler {
 public:
  explicit Scheduler(ApplicationInterface& app, SceneManager& sceneManager);
  void init();
  void update(sf::Time dt);

 private:
  ApplicationInterface& app;
  SceneManager& sceneManager;
};

}  // namespace loki::system