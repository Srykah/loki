#include "Sprite.hpp"

#include <cassert>

namespace loki::graphics {

Sprite::Sprite() {
  animator.setAnimated(sprite);
}

void Sprite::setData(const SpriteData& _data) {
  animator.resetData();
  data = &_data;
  sprite.setTexture(data->texture.getData());
}

void Sprite::setAnim(const std::string& anim) {
  assert(data);
  animator.setData(data->animations.at(anim));
  animator.start();
}

void Sprite::update(sf::Time delta) {
  animator.update(delta);
}

void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(sprite, states);
}

void Sprite::resetSprite() {
  sprite.setOrigin(0.f, 0.f);
  sprite.setPosition(0.f, 0.f);
  sprite.setRotation(0.f);
  sprite.setScale(1.f, 1.f);
  sprite.setColor(sf::Color::White);
}

sf::FloatRect Sprite::getLocalBounds() const {
  return sprite.getLocalBounds();
}

sf::FloatRect Sprite::getGlobalBounds() const {
  return getTransform().transformRect(sprite.getGlobalBounds());
}

}  // namespace loki::graphics
