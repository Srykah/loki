#include "SpriteComponent.hpp"

namespace loki::graphics {
void SpriteComponent::onStartInit() {
  addResources(spriteData);
}

void SpriteComponent::onFinalizeInit() {
  const auto& data = spriteData.getData();
  sprite.setData(data);
  if (!data.animations.empty())
    sprite.setAnim(data.animations.begin()->first);
}

void SpriteComponent::onUpdate(sf::Time delta) {
  sprite.update(delta);
}

system::DrawOrder SpriteComponent::getDrawOrder() const {
  return {};
}

void SpriteComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getGlobalTransform();
  target.draw(sprite, states);
}
}  // namespace loki::graphics