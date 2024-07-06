#pragma once

#include <loki/system/ecs/Component.hpp>
#include <loki/tiles/TileMapData.hpp>

namespace loki::tiles {

class TileMapDataComponent : public system::Component {
 public:
  system::ResourceHandle<TileMapDataResource>& getDataHandle();

 private:
  system::ResourceHandle<TileMapDataResource> tileMapData;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(TileMapDataComponent)
};

}  // namespace loki::tiles

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::Component, loki::tiles::TileMapDataComponent)
LOKI_REFLECTION_CLASS_FIELD(loki::tiles::TileMapDataComponent, tileMapData)
LOKI_REFLECTION_CLASS_END_RTTI(loki::tiles::TileMapDataComponent)