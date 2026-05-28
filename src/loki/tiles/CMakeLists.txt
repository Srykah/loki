loki_create_module(tiles
  HEADERS
  registerTypes.hpp
  TileMapData.hpp
  TileMapDataComponent.hpp
  TileSetData.hpp

  SOURCES
  registerTypes.cpp
  TileMapDataComponent.cpp

  PUBLIC_DEPS
  loki::system
)