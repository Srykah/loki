loki_create_module(system
  HEADERS
  main.hpp
  # app
  app/Application.hpp
  # ecs
  ecs/Actor.hpp
  ecs/ActorManager.hpp
  ecs/Component.hpp
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
  # window
  window/Camera.hpp
  window/WindowStyle.hpp
  window/Window.hpp

  SOURCES
  # app
  app/Application.cpp
  # ecs
  ecs/ActorManager.cpp
  # input
  input/EventHandler.cpp
  input/InputSettings.cpp
  input/InputType.cpp
  # res
  res/ResourceHolder.cpp
  # scene
  scene/Scene.cpp
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