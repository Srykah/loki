loki_create_module(system
  HEADERS
  # app
  app/ApplicationInterface.hpp
  # ecs
  ecs/Actor.hpp
  ecs/ActorHierarchy.hpp
  ecs/Component.hpp
  ecs/Component.hxx
  ecs/componentMacros.hpp
  ecs/ComponentRegistry.hpp
  ecs/ComponentRegistry.hxx
  ecs/ComponentTraits.hpp
  ecs/ComponentVisitor.hpp
  # fs
  fs/FileCategory.hpp
  fs/FileManager.hpp
  # input
  input/InputConfig.hpp
  input/InputModule.hpp
  input/InputMethod.hpp
  input/InputState.hpp
  input/InputTriggers.hpp
  input/PlayerConfig.hpp
  # modules
  modules/GameModule.hpp
  # render
  render/DrawOrder.hpp
  render/RenderQueue.hpp
  render/RendererModule.hpp
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
  # scheduler
  scheduler/UpdateTraits.hpp
  scheduler/Scheduler.hpp
  scheduler/UpdateSteps.hpp
  # window
  window/Camera.hpp
  window/Window.hpp
  window/WindowModule.hpp
  window/WindowStyle.hpp

  SOURCES
  # ecs
  ecs/Actor.cpp
  ecs/Component.cpp
  ecs/ComponentRegistry.cpp
  # fs
  fs/FileManager.cpp
  # input
  input/InputModule.cpp
  input/InputMethod.cpp
  input/InputTriggers.cpp
  # render
  render/RenderQueue.cpp
  render/RendererModule.cpp
  # res
  res/ResourceHolder.cpp
  # scene
  scene/Scene.cpp
  scene/SceneManager.cpp
  # scheduler
  scheduler/Scheduler.cpp
  # window
  window/Camera.cpp
  window/Window.cpp
  window/WindowModule.cpp
  window/WindowStyle.cpp

  PUBLIC_DEPS
  loki::core
  EnTT::EnTT
  ImGui-SFML::ImGui-SFML
)