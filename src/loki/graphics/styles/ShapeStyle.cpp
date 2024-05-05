#include "ShapeStyle.hpp"

namespace loki::graphics {

void ShapeStyle::applyTo(sf::Shape& shape) const {
  shape.setTexture(texture);
  if (textureRect != sf::IntRect{}) {
    shape.setTextureRect(textureRect);
  }
  shape.setFillColor(fillColor);
  shape.setOutlineColor(outlineColor);
  shape.setOutlineThickness(outlineThickness);
}

}  // namespace loki::graphics
