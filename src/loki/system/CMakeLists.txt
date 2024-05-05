loki_create_module(system
  HEADERS
  main.hpp
  # app
  app/Application.hpp
  # ecs
  ecs/Actor.hpp
  ecs/Component.hpp
  ecs/componentMacros.hpp
  ecs/ComponentRegistry.hpp
  ecs/ComponentRegistry.hxx
  ecs/ComponentSlot.hpp
  ecs/DrawableComponent.hpp
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
  res/LogicResource.hpp
  res/Resource.hpp
  res/ResourceHandle.hpp
  res/ResourceHolder.hpp
  res/ResourceHolder.hxx
  res/ResourceListener.hpp
  res/SFMLResources.hpp
  # scene
  scene/Scene.hpp
  scene/SceneManager.hpp
  # window
  window/Camera.hpp
  window/Window.hpp
  window/WindowStyle.hpp

  SOURCES
  # app
  app/Application.cpp
  # ecs
  ecs/Actor.cpp
  ecs/Component.cpp
  ecs/ComponentSlot.cpp
  ecs/ComponentRegistry.cpp
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
  # window
  window/Camera.cpp
  window/Window.cpp
  window/WindowStyle.cpp

  PUBLIC_DEPS
  loki::core
  sfml-graphics
  #nlohmann_json::nlohmann_json
  EnTT::EnTT
  ImGui-SFML::ImGui-SFML
)