loki_create_module(system
  HEADERS
  main.hpp
  # app
  app/Application.hpp
  app/ServiceRegistry.hpp
  # ecs
  ecs/Actor.hpp
  ecs/Actor.hxx
  ecs/ActorManager.hpp
  ecs/Component.hpp
  ecs/ComponentGroup.hpp
  ecs/ComponentGroup.hxx
  # fs
  fs/FileCategory.hpp
  fs/FileManager.hpp
  # input
  input/InputConfig.hpp
  input/InputManager.hpp
  input/InputMethod.hpp
  input/InputState.hpp
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
  scene/SceneElement.hpp
  scene/SceneManager.hpp
  scene/SceneNode.hpp
  # window
  window/Camera.hpp
  window/Window.hpp
  window/WindowStyle.hpp

  SOURCES
  # app
  app/Application.cpp
  # ecs
  ecs/Actor.cpp
  ecs/ActorManager.cpp
  # fs
  fs/FileManager.cpp
  # input
  input/InputManager.cpp
  input/InputMethod.cpp
  # res
  res/ResourceHolder.cpp
  # scene
  scene/Scene.cpp
  scene/SceneManager.cpp
  scene/SceneNode.cpp
  # window
  window/Camera.cpp
  window/Window.cpp
  window/WindowStyle.cpp

  PUBLIC_DEPS
  loki::core
  sfml-graphics
  nlohmann_json::nlohmann_json
  EnTT::EnTT
  )