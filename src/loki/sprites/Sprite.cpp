/*!
 * \file SpriteView.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "Sprite.hpp"

namespace loki::sprites {

Sprite::Sprite(const SpriteViewData& viewData, const sf::String& anim)
    : viewData(viewData),
      animator(std::make_unique<anim::Animator<sf::Sprite>>(
          sprite,
          viewData.animations.at(anim))) {
  sprite.setTexture(viewData.texture);
}

void Sprite::setAnim(const sf::String& anim) {
  animator = std::make_unique<anim::Animator<sf::Sprite>>(
      sprite, viewData.animations.at(anim));
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

}  // namespace loki::sprites
