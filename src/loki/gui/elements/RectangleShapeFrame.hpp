#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include "Frame.hpp"
#include <loki/graphics/styles/ShapeStyle.hpp>

namespace loki::gui {

class RectangleShapeFrame : public Frame {
 public:
  RectangleShapeFrame(sf::Vector2f size,
                      float padding,
                      const graphics::ShapeStyle& style);
  sf::FloatRect getInternalBounds() const override;

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  float padding;
  sf::RectangleShape shape;
};

}  // namespace loki::gui
