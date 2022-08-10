/*!
 * \file SpriteView.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "Sprite.hpp"

namespace loki::sprites {

Sprite::Sprite(const SpriteData& data, const std::string& anim) : data(data) {
  setAnim(anim);
  sprite.setTexture(data.texture.getData());
}

void Sprite::setAnim(const std::string& anim) {
  animator = std::make_unique<anim::ShapeAnimator<sf::Sprite>>(
      sprite, data.animations.at(anim));
}

void Sprite::update(sf::Time delta) {
  animator->update(delta);
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

}  // namespace loki::sprites
