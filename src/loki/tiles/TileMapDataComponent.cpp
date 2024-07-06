#include "TileMapDataComponent.hpp"

namespace loki::tiles {

system::ResourceHandle<TileMapDataResource>& TileMapDataComponent::getDataHandle() {
  return tileMapData;
}
}  // namespace loki::tiles