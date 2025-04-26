#include "TileMapDataComponent.hpp"

#include <math/Vector2Ops.hpp>

namespace loki::tiles {

system::ResourceHandle<TileMapDataResource>& TileMapDataComponent::getDataHandle() {
  return tileMapData;
}

#if 0
sf::FloatRect TileMapDataComponent::getBoundingBox() const {
  if (!tileMapData || !tileMapData->tileset)
    return {};

  const auto* tileSizeAttr = tileMapData->tileset->getTileSetAttribute<SizeTileSetAttribute>();
  if (!tileSizeAttr)
    return {};

  return {{0, 0}, {core::compMult(tileMapData->mapSize, tileSizeAttr->tileSize)}};
}
#endif

}  // namespace loki::tiles