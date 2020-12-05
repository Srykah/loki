/*!
 * \file AnimationView.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics.hpp>
#include "loki/sprites/model/AnimationData.hpp"

namespace loki::sprites {

class AnimationView : public sf::Drawable, public sf::Transformable {
 public:
  explicit AnimationView(const AnimationData& data, const sf::Texture* extTexture = nullptr);
  void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const override;
  void update(const sf::Time& delta);

 private:
  void updateCurrentFrame();

 private:
  const AnimationData& data;
  sf::Sprite sprite;
  int frameIndex;
  sf::Time timeSinceLastFrame;
};

}
