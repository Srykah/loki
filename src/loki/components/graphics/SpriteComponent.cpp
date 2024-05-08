#include "SpriteComponent.hpp"

namespace loki::components {
void SpriteComponent::onStartInit() {
  addResources(spriteData);
}

void SpriteComponent::onFinalizeInit() {
  const auto& data = spriteData.getData();
  sprite.setData(data);
  if (!data.animations.empty())
    sprite.setAnim(data.animations.begin()->first);
}

void SpriteComponent::update(sf::Time dt) {
  sprite.update(dt);
}

[[nodiscard]] system::DrawOrder SpriteComponent::getDrawOrder() const {
  return {};
}

void SpriteComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getGlobalTransform();
  target.draw(sprite, states);
}
}  // namespace loki::components