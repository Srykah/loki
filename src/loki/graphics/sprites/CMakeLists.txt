loki_create_lib(
  NAME sprites MODULE graphics
  HEADERS
  Sprite.hpp
  SpriteData.hpp
  #SpriteViewData.hpp
  SOURCES
  Sprite.cpp
  #SpriteData.cpp
  #SpriteViewData.cpp
  PUBLIC_DEPS
  loki::anim
  sfml-graphics
  sfml-window
  sfml-system
)
