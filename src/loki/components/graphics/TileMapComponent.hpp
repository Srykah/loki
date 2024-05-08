#pragma once

#include <loki/system/ecs/DrawableComponent.hpp>

#include "loki/graphics/tiles/TileMap.hpp"

namespace loki::components {
class TileMapComponent : public system::DrawableComponent {
 public:
  void onStartInit() override;
  void onFinalizeInit() override;
  [[nodiscard]] system::DrawOrder getDrawOrder() const override;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  system::ResourceHandle<graphics::TileMapDataResource> tileMapData;
  graphics::TileMap tileMap;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(TileMapComponent)
};

}  // namespace loki::components

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::Component, loki::components::TileMapComponent)
LOKI_REFLECTION_CLASS_FIELD(loki::components::TileMapComponent, tileMapData)
LOKI_REFLECTION_CLASS_END_RTTI(loki::components::TileMapComponent)