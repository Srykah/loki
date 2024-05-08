#pragma once

#include <vector>

#include <loki/graphics/tiles/TileSetData.hpp>

namespace loki::graphics {

struct TileMapData {
  system::ResourceHandle<TileSetDataResource> tileset;
  sf::Vector2u mapSize;
  std::vector<int> tiles;
};

struct TileMapDataResource : public system::LogicResource<TileMapData> {
  LOKI_LOGICRESOURCE_ADD_CHILDREN_TO_HOLDER(tileset)
};

}  // namespace loki::graphics

LOKI_REFLECTION_CLASS_BEGIN(loki::graphics::TileMapData)
LOKI_REFLECTION_CLASS_FIELD(loki::graphics::TileMapData, tileset)
LOKI_REFLECTION_CLASS_FIELD(loki::graphics::TileMapData, mapSize)
LOKI_REFLECTION_CLASS_FIELD(loki::graphics::TileMapData, tiles)
LOKI_REFLECTION_CLASS_END()

LOKI_REFLECTION_CLASS_BEGIN(loki::graphics::TileMapDataResource)
LOKI_REFLECTION_CLASS_END()