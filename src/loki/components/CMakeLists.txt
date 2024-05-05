loki_create_module(components
  HEADERS
  graphics/CircleShapeComponent.hpp
  graphics/SpriteComponent.hpp
  registerComponents.hpp

  SOURCES
  graphics/CircleShapeComponent.cpp
  graphics/SpriteComponent.cpp
  registerComponents.cpp

  PUBLIC_DEPS
  loki::system
  loki::graphics)