#include "SpriteComponent.hpp"

#include <loki/system/render/RendererModule.hpp>

namespace loki::graphics {
void SpriteComponent::onStartInit() {
  addResources(spriteData);
}

void SpriteComponent::onFinalizeInit() {
  const auto& data = spriteData.getData();
  sprite.setData(data);
  if (!data.animations.empty())
    sprite.setAnim(data.animations.begin()->first);
  getService<system::RendererModule>().getRenderQueue().registerDrawable(this, getDrawOrder());
}

void SpriteComponent::onUpdate(sf::Time delta) {
  sprite.update(delta);
}

system::DrawOrder SpriteComponent::getDrawOrder() const {
  return {1};
}

void SpriteComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getGlobalTransform();
  target.draw(sprite, states);
}
}  // namespace loki::graphics