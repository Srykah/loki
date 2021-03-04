/*!
 * \file SpriteView.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "SpriteView.hpp"

namespace loki::sprites {

SpriteView::SpriteView(const SpriteData& data) {
  setData(data);
}

void SpriteView::setData(const SpriteData& _data) {
  data = &_data;
}

void SpriteView::setAnim(const std::string& anim) {
  auto extTexture = data->texture.has_value() ? &data->texture.value() : nullptr;
  view = std::make_unique<AnimationView>(data->animations.at(anim), extTexture);

  setElapsedTime(sf::Time::Zero);
  sf::Time animDuration;
  for (const auto& frame : data->animations.at(anim).frames) {
    animDuration += frame.duration;
  }
  setDuration(animDuration);
}

void SpriteView::update(sf::Time delta) {
  Animated::update(delta);
  view->update(delta);
}

void SpriteView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(*view, states);
}

}
