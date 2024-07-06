#include "GraphicsTileMapComponent.hpp"

#include "loki/tiles/TileMapDataComponent.hpp"

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
}

[[nodiscard]] system::DrawOrder GraphicsTileMapComponent::getDrawOrder() const {
  return {};
}

void GraphicsTileMapComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getGlobalTransform();
  target.draw(tileMap, states);
}
}  // namespace loki::graphics