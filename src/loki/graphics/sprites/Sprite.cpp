#include "Sprite.hpp"

#include <cassert>

namespace loki::graphics {

void Sprite::setData(const SpriteData& _data) {
  animator.resetData();
  data = &_data;
  sprite.emplace(data->texture.getData());
  animator.setAnimated(*sprite);
}

void Sprite::setAnim(const std::string& anim) {
  assert(data && sprite);
  animator.setData(data->animations.at(anim));
  animator.start();
}

void Sprite::start() {
  assert(sprite);
  animator.start();
  animator.setTime(sf::Time::Zero);
}

void Sprite::update(sf::Time delta) {
  assert(sprite);
  animator.update(delta);
}

void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  assert(sprite);
  states.transform *= getTransform();
  target.draw(*sprite, states);
}

void Sprite::reset() {
  sprite.reset();
  animator.resetData();
}

sf::FloatRect Sprite::getLocalBounds() const {
  return sprite ? sprite->getLocalBounds() : sf::FloatRect{};
}

sf::FloatRect Sprite::getGlobalBounds() const {
  return sprite ? getTransform().transformRect(sprite->getGlobalBounds()) : sf::FloatRect{};
}

}  // namespace loki::graphics
