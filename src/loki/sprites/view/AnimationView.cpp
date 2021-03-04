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
, curFrameStartTime(sf::Time::Zero) {
  if (data.texture.has_value()) {
    sprite.setTexture(data.texture.value());
  } else {
    sprite.setTexture(*extTexture);
  }

  sf::Time totalDuration;
  for (const auto& frame : data.frames) {
    totalDuration += frame.duration;
  }
  setDuration(totalDuration);

  updateCurrentFrame();
}

void AnimationView::draw(
    sf::RenderTarget& target,
    sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(sprite, states);
}

void AnimationView::update(sf::Time delta) {
  Animated::update(delta);
  bool needUpdate = false;
  while (getElapsedTime() - curFrameStartTime >= data.frames.at(frameIndex).duration) {
    curFrameStartTime += data.frames.at(frameIndex).duration;
    ++frameIndex;
    if (frameIndex == data.frames.size()) {
      frameIndex = 0;
      setElapsedTime(getElapsedTime() - curFrameStartTime);
      curFrameStartTime = sf::Time::Zero;
    }
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
