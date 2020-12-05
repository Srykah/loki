/*!
 * \file AnimationView.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "AnimationView.hpp"
namespace loki::sprites {

AnimationView::AnimationView(
    const loki::sprites::AnimationData& data,
    const sf::Texture* extTexture)
: data(data)
, frameIndex(0)
, timeSinceLastFrame(sf::Time::Zero) {
  if (data.texture.has_value()) {
    sprite.setTexture(data.texture.value());
  } else {
    sprite.setTexture(*extTexture);
  }
  updateCurrentFrame();
}

void AnimationView::draw(
    sf::RenderTarget& target,
    sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(sprite, states);
}

void AnimationView::update(const sf::Time& delta) {
  bool needUpdate = false;
  timeSinceLastFrame += delta;
  while (timeSinceLastFrame >= data.frames.at(frameIndex).duration) {
    timeSinceLastFrame -= data.frames.at(frameIndex).duration;
    frameIndex = (frameIndex + 1) % data.frames.size();
    needUpdate = true;
  }
  if (needUpdate) {
    updateCurrentFrame();
  }
}

void AnimationView::updateCurrentFrame() {
  const auto& frameData = data.frames.at(frameIndex);
  sprite.setTextureRect(frameData.rect);
  sprite.setOrigin(frameData.origin);
}

}
