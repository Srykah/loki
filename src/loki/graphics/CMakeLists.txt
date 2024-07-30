loki_create_module(graphics
  HEADERS
  # anim
  anim/ShapeAnimationData.hpp
  anim/ShapeAnimator.hpp
  anim/ADLHelpers.hpp
  anim/ShapeAnimator.hxx
  # shapes
  shapes/Capsule.hpp
  shapes/RoundedRectangle.hpp
  # sprites
  sprites/Sprite.hpp
  sprites/SpriteData.hpp
  sprites/SpriteViewData.hpp
  sprites/SpriteComponent.hpp
  # styles
  styles/ShapeStyle.hpp
  styles/TextStyle.hpp
  # text
  text/AnimatedText.hpp
  text/AnimatedTextStyle.hpp
  text/AnnotatedStringEngine.hpp
  text/AnnotatedText.hpp
  text/Stylesheet.hpp
  text/AnimatedGlyph.hpp
  # tiles
  tiles/GraphicsTileMap.hpp
  tiles/GraphicsTileMapComponent.hpp
  tiles/TextureTileSetAttribute.hpp

  SOURCES
  # shapes
  shapes/Capsule.cpp
  shapes/RoundedRectangle.cpp
  # sprites
  sprites/Sprite.cpp
  sprites/SpriteViewData.cpp
  sprites/SpriteComponent.cpp
  # styles
  styles/ShapeStyle.cpp
  styles/TextStyle.cpp
  # text
  text/AnimatedText.cpp
  text/AnimatedTextStyle.cpp
  text/AnnotatedStringEngine.cpp
  text/AnnotatedText.cpp
  text/Stylesheet.cpp
  text/AnimatedGlyph.cpp
  # tiles
  tiles/GraphicsTileMap.cpp
  tiles/GraphicsTileMapComponent.cpp

  PUBLIC_DEPS
  loki::tiles
)