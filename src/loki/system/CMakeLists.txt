loki_create_module(system
  HEADERS
  # system
  app/Application.hpp
  # input
  input/EventHandler.hpp
  input/InputSettings.hpp
  input/InputState.hpp
  input/InputType.hpp
  input/PlayerConfig.hpp
  # system
  res/JsonResources.hpp
  res/Resource.hpp
  res/ResourceHandle.hpp
  res/ResourceHolder.hpp
  res/ResourceHolder.hxx
  res/SFMLResources.hpp
  # scene
  scene/Scene.hpp
  # system
  screens/Screen.hpp
  screens/Screen.hxx
  screens/ScreenStack.hpp
  screens/Signal.hpp
  # window
  window/Camera.hpp
  window/WindowStyle.hpp
  window/Window.hpp

  SOURCES
  # system
  app/Application.cpp
  # input
  input/EventHandler.cpp
  input/InputSettings.cpp
  input/InputType.cpp
  # system
  res/ResourceHolder.cpp
  # scene
  scene/Scene.cpp
  # system
  screens/Screen.cpp
  screens/ScreenStack.cpp
  # window
  window/Camera.cpp
  window/WindowStyle.cpp
  window/Window.cpp

  PUBLIC_DEPS
  loki::core
  sfml-graphics
  nlohmann_json::nlohmann_json
  EnTT::EnTT
  )