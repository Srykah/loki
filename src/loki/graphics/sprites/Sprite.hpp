#pragma once

#include <SFML/Graphics.hpp>

#include <loki/graphics/anim/ShapeAnimator.hpp>
#include <loki/graphics/sprites/SpriteData.hpp>

namespace loki::graphics {

class Sprite : public sf::Drawable, public sf::Transformable {
 public:
  Sprite();

  void setData(const SpriteData& data);
  void setAnim(const std::string& anim);

  void update(sf::Time delta);

  sf::FloatRect getLocalBounds() const;
  sf::FloatRect getGlobalBounds() const;

 private:
  void draw(sf::RenderTarget& target, sf::RenderStates states = {}) const override;

  void resetSprite();

 private:
  const SpriteData* data = nullptr;
  sf::Sprite sprite;
  ShapeAnimator<sf::Sprite> animator;
};

}  // namespace loki::graphics
