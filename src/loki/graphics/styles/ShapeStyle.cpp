/*!
 * \file RectangleShapeStyle.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "ShapeStyle.hpp"

namespace loki::styles {

void ShapeStyle::applyTo(sf::Shape& shape) const {
  shape.setTexture(texture);
  if (textureRect != sf::IntRect {}) {
    shape.setTextureRect(textureRect);
  }
  shape.setFillColor(fillColor);
  shape.setOutlineColor(outlineColor);
  shape.setOutlineThickness(outlineThickness);
}

}
