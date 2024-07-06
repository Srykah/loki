#pragma once

#include <loki/system/ecs/Component.hpp>
#include <loki/system/render/Drawable.hpp>
#include <loki/graphics/tiles/GraphicsTileMap.hpp>

namespace loki::graphics {
class GraphicsTileMapComponent : public system::Component, public system::Drawable {
 public:
  void onStartInit() override;
  void onFinalizeInit() override;
  [[nodiscard]] system::DrawOrder getDrawOrder() const override;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  GraphicsTileMap tileMap;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(GraphicsTileMapComponent)
};

}  // namespace loki::graphics

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::Component, loki::graphics::GraphicsTileMapComponent)
LOKI_REFLECTION_CLASS_END_RTTI(loki::graphics::GraphicsTileMapComponent)