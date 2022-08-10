loki_create_module(graphics
  HEADERS
  # anim
  anim/ShapeAnimationData.hpp
  anim/ShapeAnimator.hpp
  anim/ADLHelpers.hpp
  anim/ShapeAnimator.hxx
  anim/TemplateHelpers.hpp
  # anim-editor
  anim-editor/AnimEditor.hpp
  # shapes
  shapes/Capsule.hpp
  shapes/RoundedRectangle.hpp
  # sprites
  sprites/Sprite.hpp
  sprites/SpriteData.hpp
  sprites/SpriteViewData.hpp
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
  tiles/LayerData.hpp
  tiles/LayerView.hpp
  tiles/MapData.hpp
  tiles/MapView.hpp
  tiles/ObjectData.hpp
  tiles/ObjectLayerData.hpp
  tiles/ObjectLayerView.hpp
  tiles/Property.hpp
  tiles/TerrainData.hpp
  tiles/TextData.hpp
  tiles/TileData.hpp
  tiles/TileLayerData.hpp
  tiles/TileLayerView.hpp
  tiles/TilesetData.hpp

  SOURCES
  # anim-editor
  anim-editor/AnimEditor.cpp
  # shapes
  shapes/Capsule.cpp
  shapes/RoundedRectangle.cpp
  # sprites
  sprites/Sprite.cpp
  sprites/SpriteViewData.cpp
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
  tiles/LayerData.cpp
  tiles/MapData.cpp
  tiles/MapView.cpp
  tiles/ObjectData.cpp
  tiles/ObjectLayerData.cpp
  tiles/ObjectLayerView.cpp
  tiles/Property.cpp
  tiles/TextData.cpp
  tiles/TileData.cpp
  tiles/TileLayerData.cpp
  tiles/TileLayerView.cpp
  tiles/TilesetData.hpp

  PUBLIC_DEPS
  loki::core
  sfml-graphics
  nlohmann_json::nlohmann_json
  )