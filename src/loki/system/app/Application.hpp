#pragma once

#include <loki/core/runtimeObject/RuntimeObjectRegistry.hpp>
#include <loki/core/services/ServiceRegistry.hpp>
#include <loki/system/ecs/ComponentRegistry.hpp>
#include <loki/system/input/InputManager.hpp>
#include <loki/system/res/ResourceHolder.hpp>
#include <loki/system/scene/SceneManager.hpp>
#include <loki/system/window/Window.hpp>

namespace loki::system {
class Application {
 public:
  virtual ~Application();
  int run(int argc, char** argv);

 protected:
  virtual void registerServices();
  virtual int parseArgs(int argc, char** argv) { return 0; }
  virtual void init();  // after argument parsing

 private:
  void loop();

 protected:
  ServiceRegistry serviceRegistry;

 private:
  core::RuntimeObjectRegistry runtimeObjectRegistry;
  ComponentRegistry componentRegistry;
  InputManager inputManager;
  ResourceHolder resourceHolder;
  SceneManager sceneManager;
  Window window;
};

}  // namespace loki::system
