#pragma once

#include <loki/system/ecs/DrawableComponent.hpp>
#include <loki/graphics/tiles/GraphicsTileMap.hpp>

namespace loki::graphics {
class GraphicsTileMapComponent : public system::DrawableComponent {
 public:
  void onStartInit() override;
  void onFinalizeInit() override;
  [[nodiscard]] system::DrawOrder getDrawOrder() const override;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  system::ResourceHandle<tiles::TileMapDataResource> tileMapData;
  GraphicsTileMap tileMap;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(GraphicsTileMapComponent)
};

}  // namespace loki::graphics

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::Component, loki::graphics::GraphicsTileMapComponent)
LOKI_REFLECTION_CLASS_FIELD(loki::graphics::GraphicsTileMapComponent, tileMapData)
LOKI_REFLECTION_CLASS_END_RTTI(loki::graphics::GraphicsTileMapComponent)