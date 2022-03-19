/*!
 * \file RectangleShapeStyle.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace loki::styles {

struct ShapeStyle {
  const sf::Texture* texture = nullptr;
  sf::IntRect textureRect;
  sf::Color fillColor = sf::Color::White;
  sf::Color outlineColor = sf::Color::White;
  float outlineThickness = 0.f;

  void applyTo(sf::Shape& shape) const;
};

}  // namespace loki::styles
