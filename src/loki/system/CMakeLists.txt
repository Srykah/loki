loki_create_module(system
  HEADERS
  # app
  app/Application.hpp
  # input
  input/EventHandler.hpp
  input/InputSettings.hpp
  input/InputState.hpp
  input/InputType.hpp
  input/PlayerConfig.hpp
  # res
  res/JsonResources.hpp
  res/Resource.hpp
  res/ResourceHandle.hpp
  res/ResourceHolder.hpp
  res/ResourceHolder.hxx
  res/SFMLResources.hpp
  # scene
  scene/Scene.hpp
  # screens
  screens/Screen.hpp
  screens/Screen.hxx
  screens/ScreenStack.hpp
  screens/Signal.hpp
  # window
  window/Camera.hpp
  window/Style.hpp
  window/Window.hpp

  SOURCES
  # app
  app/Application.cpp
  # input
  input/EventHandler.cpp
  input/InputSettings.cpp
  input/InputType.cpp
  # res
  res/ResourceHolder.cpp
  # scene
  scene/Scene.hpp
  # screens
  screens/Screen.cpp
  screens/ScreenStack.cpp
  # window
  window/Camera.cpp
  window/Style.cpp
  window/Window.cpp

  PUBLIC_DEPS
  loki::core
  sfml-graphics
  nlohmann_json::nlohmann_json
  )