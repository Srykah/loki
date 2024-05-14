#pragma once

#include <loki/system/ecs/DrawableComponent.hpp>
#include <loki/graphics/tiles/TileMap.hpp>

namespace loki::graphics {
class TileMapComponent : public system::DrawableComponent {
 public:
  void onStartInit() override;
  void onFinalizeInit() override;
  [[nodiscard]] system::DrawOrder getDrawOrder() const override;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  system::ResourceHandle<TileMapDataResource> tileMapData;
  TileMap tileMap;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(TileMapComponent)
};

}  // namespace loki::graphics

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::Component, loki::graphics::TileMapComponent)
LOKI_REFLECTION_CLASS_FIELD(loki::graphics::TileMapComponent, tileMapData)
LOKI_REFLECTION_CLASS_END_RTTI(loki::graphics::TileMapComponent)