#pragma once

#include <loki/system/ecs/Component.hpp>
#include <loki/graphics/tiles/GraphicsTileMap.hpp>

namespace loki::graphics {
class GraphicsTileMapComponent : public system::Component, public sf::Drawable {
 public:
  void onBeginInit() override;
  void onEndInit() override;
  [[nodiscard]] system::DrawOrder getDrawOrder() const;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  GraphicsTileMap tileMap;

  LOKI_RTTI_CLASS_DECLARE(GraphicsTileMapComponent)
};

}  // namespace loki::graphics

LOKI_REFLECTION_COMPONENT_BEGIN(loki::graphics::GraphicsTileMapComponent)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::graphics::GraphicsTileMapComponent)