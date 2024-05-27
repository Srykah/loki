loki_create_module(tiles
  HEADERS
  TileMapData.hpp
  TileSetData.hpp

  SOURCES
  dummy.cpp

  PUBLIC_DEPS
  loki::core
  loki::system
  EnTT::EnTT
  sfml-graphics
  yaml-cpp::yaml-cpp
)