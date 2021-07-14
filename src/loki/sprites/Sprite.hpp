/*!
 * \file SpriteView.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <loki/anim/Animator.hpp>
#include "SpriteViewData.hpp"

namespace loki::sprites {

class Sprite : public sf::Drawable, public sf::Transformable {
 public:
  explicit Sprite(const SpriteViewData& viewData, const sf::String& anim);

  void setAnim(const sf::String& anim);

  void update(sf::Time delta);

  sf::FloatRect getLocalBounds() const;
  sf::FloatRect getGlobalBounds() const;

 private:
  void draw(sf::RenderTarget& target,
            sf::RenderStates states = sf::RenderStates()) const override;

  void resetSprite();

 private:
  const SpriteViewData& viewData;
  sf::Sprite sprite;
  std::unique_ptr<anim::Animator<sf::Sprite>> animator;
};

}
