/**
 * \file Application.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <loki/system/input/EventHandler.hpp>
#include <loki/system/res/ResourceHolder.hpp>
#include <loki/system/screens/ScreenStack.hpp>
#include <loki/system/window/Window.hpp>

namespace loki::app {
class Application {
 public:
  void run(int argc, char** argv);

 protected:
  window::Window window;
  input::EventHandler eventHandler;
  res::ResourceHolder resourceHolder;
  screens::ScreenStack screenStack;
};
}  // namespace loki::app