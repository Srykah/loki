#pragma once

#include <SFML/Graphics.hpp>

#include <loki/graphics/anim/ShapeAnimator.hpp>

#include "SpriteData.hpp"

namespace loki::gfx {

class Sprite : public sf::Drawable, public sf::Transformable {
 public:
  explicit Sprite(const SpriteData& data, const std::string& anim);

  void setAnim(const std::string& anim);

  void update(sf::Time delta);

  sf::FloatRect getLocalBounds() const;
  sf::FloatRect getGlobalBounds() const;

 private:
  void draw(sf::RenderTarget& target,
            sf::RenderStates states = sf::RenderStates()) const override;

  void resetSprite();

 private:
  const SpriteData& data;
  sf::Sprite sprite;
  std::unique_ptr<gfx::ShapeAnimator<sf::Sprite>> animator;
};

}  // namespace loki::gfx
