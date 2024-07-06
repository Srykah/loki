loki_create_module(tiles
  HEADERS
  TileMapData.hpp
  TileMapDataComponent.hpp
  TileSetData.hpp

  SOURCES
  TileMapDataComponent.cpp

  PUBLIC_DEPS
  loki::core
  loki::system
  EnTT::EnTT
  sfml-graphics
  yaml-cpp::yaml-cpp
)