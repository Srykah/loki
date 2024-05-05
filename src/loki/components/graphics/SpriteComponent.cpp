#include "SpriteComponent.hpp"

#include <loki/core/services/ServiceRegistry.hpp>

namespace loki::components {
void SpriteComponent::init() {
  std::println(stderr, "init");
  getService<system::ResourceHolder>().add(spriteData, this);
}

void SpriteComponent::onResourcesLoaded() {
  std::println(stderr, "onResourcesLoaded");
  const auto& data = spriteData.getData();
  sprite.setData(data);
  if (!data.animations.empty())
    sprite.setAnim(data.animations.begin()->first);
  isInit = true;
}

void SpriteComponent::update(sf::Time dt) {
  if (!isInit)
    return;
  std::println(stderr, "update");
  sprite.update(dt);
}

[[nodiscard]] system::DrawOrder SpriteComponent::getDrawOrder() const {
  std::println(stderr, "getDrawOrder");
  return {};
}

void SpriteComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  if (!isInit)
    return;
  std::println(stderr, "draw");
  states.transform *= getTransform();
  target.draw(sprite, states);
}
}  // namespace loki::components