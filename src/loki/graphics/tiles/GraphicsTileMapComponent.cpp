#include "GraphicsTileMapComponent.hpp"

#include <loki/system/render/RendererModule.hpp>
#include <loki/tiles/TileMapDataComponent.hpp>

namespace loki::graphics {
void GraphicsTileMapComponent::onStartInit() {
  auto* dataComp = getActor().getComponent<tiles::TileMapDataComponent>();
  assert(dataComp);
  addResources(dataComp->getDataHandle());
}

void GraphicsTileMapComponent::onFinalizeInit() {
  auto* dataComp = getActor().getComponent<tiles::TileMapDataComponent>();
  assert(dataComp);
  tileMap.setData(dataComp->getDataHandle().getData());
  getService<system::RendererModule>().getRenderQueue().registerDrawable(this, getDrawOrder());
}

system::DrawOrder GraphicsTileMapComponent::getDrawOrder() const {
  return {};
}

void GraphicsTileMapComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getGlobalTransform();
  target.draw(tileMap, states);
}
}  // namespace loki::graphics