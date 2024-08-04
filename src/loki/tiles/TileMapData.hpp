#pragma once

#include <vector>

#include <SFML/System/Vector2.hpp>

#include <loki/core/reflection/sfmlTypesInfo.hpp>
#include <loki/system/res/LogicResource.hpp>
#include <loki/tiles/TileSetData.hpp>

namespace loki::tiles {

struct TileMapData {
  system::ResourceHandle<TileSetDataResource> tileset;
  sf::Vector2u mapSize;
  std::vector<int> tiles;
};

struct TileMapDataResource : public system::LogicResource<TileMapData> {
  LOKI_LOGICRESOURCE_ADD_CHILDREN_TO_HOLDER(tileset)
};

}  // namespace loki::tiles

LOKI_REFLECTION_CLASS_BEGIN(loki::tiles::TileMapData)
LOKI_REFLECTION_CLASS_FIELD(tileset)
LOKI_REFLECTION_CLASS_FIELD(mapSize)
LOKI_REFLECTION_CLASS_FIELD(tiles)
LOKI_REFLECTION_CLASS_END()

LOKI_REFLECTION_CLASS_BEGIN(loki::tiles::TileMapDataResource)
LOKI_REFLECTION_CLASS_END()