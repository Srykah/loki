#pragma once

#include <loki/system/ecs/ActorManager.hpp>
#include <loki/system/input/EventHandler.hpp>
#include <loki/system/res/ResourceHolder.hpp>
#include <loki/system/scene/Scene.hpp>
#include <loki/system/screens/ScreenStack.hpp>
#include <loki/system/window/Window.hpp>

namespace loki::system {
class Application {
 public:
  int run(int argc, char** argv);

 protected:
  virtual int parseArgs(int argc, char** argv) { return 0; };
  virtual void init(){};  // after argument parsing

 private:
  void loop();

 protected:
  system::Window window;
  system::ResourceHolder resourceHolder;
  system::EventHandler eventHandler;
  system::ActorManager actorManager;
  system::Scene scene;
};

std::unique_ptr<loki::system::Application> getApplication();

}  // namespace loki::system
