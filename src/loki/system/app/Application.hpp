#pragma once

#include <loki/system/ecs/ActorManager.hpp>
#include <loki/system/input/InputManager.hpp>
#include <loki/system/res/ResourceHolder.hpp>
#include <loki/system/scene/SceneManager.hpp>
#include <loki/system/window/Window.hpp>

namespace loki::system {
class Application {
 public:
  Application();
  int run(int argc, char** argv);

 protected:
  virtual int parseArgs(int argc, char** argv) { return 0; }
  virtual void init() {}  // after argument parsing

 private:
  void loop();

 protected:
  system::Window window;
  system::ResourceHolder resourceHolder;
  system::InputManager inputManager;
  system::ActorManager actorManager;
  system::SceneManager sceneManager;
};

}  // namespace loki::system
