#include "GraphicsTileMapComponent.hpp"

namespace loki::graphics {
void GraphicsTileMapComponent::onStartInit() {
  addResources(tileMapData);
}

void GraphicsTileMapComponent::onFinalizeInit() {
  const auto& data = tileMapData.getData();
  tileMap.setData(data);
}

[[nodiscard]] system::DrawOrder GraphicsTileMapComponent::getDrawOrder() const {
  return {};
}

void GraphicsTileMapComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getGlobalTransform();
  target.draw(tileMap, states);
}
}  // namespace loki::graphics