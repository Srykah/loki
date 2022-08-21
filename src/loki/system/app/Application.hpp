#pragma once

#include <loki/system/ecs/ActorManager.hpp>
#include <loki/system/input/EventHandler.hpp>
#include <loki/system/res/ResourceHolder.hpp>
#include <loki/system/screens/ScreenStack.hpp>
#include <loki/system/window/Window.hpp>

namespace loki::system {
class Application {
 public:
  void run(int argc, char** argv);

 protected:
  system::Window window;
  system::ResourceHolder resourceHolder;
  system::EventHandler eventHandler;
  system::ActorManager actorManager;

};
}  // namespace loki::system