loki_create_module(system
  HEADERS
  # ecs
  ecs/Actor.hpp
  ecs/Component.hpp
  ecs/Component.hxx
  ecs/componentMacros.hpp
  ecs/ComponentRegistry.hpp
  ecs/ComponentRegistry.hxx
  ecs/ComponentTraits.hpp
  ecs/DrawableComponent.hpp
  ecs/ActorHierarchy.hpp
  # fs
  fs/FileCategory.hpp
  fs/FileManager.hpp
  # input
  input/InputConfig.hpp
  input/InputManager.hpp
  input/InputMethod.hpp
  input/InputState.hpp
  input/PlayerConfig.hpp
  # modules
  modules/GameModule.hpp
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
  # ecs
  ecs/Actor.cpp
  ecs/Component.cpp
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
  EnTT::EnTT
  ImGui-SFML::ImGui-SFML
  sfml-graphics
  yaml-cpp::yaml-cpp
)