#include "TileMapComponent.hpp"

namespace loki::components {
void TileMapComponent::onStartInit() {
  addResources(tileMapData);
}

void TileMapComponent::onFinalizeInit() {
  const auto& data = tileMapData.getData();
  tileMap.setData(data);
}

[[nodiscard]] system::DrawOrder TileMapComponent::getDrawOrder() const {
  return {};
}

void TileMapComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getGlobalTransform();
  target.draw(tileMap, states);
}
}  // namespace loki::components