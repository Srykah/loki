#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace loki::gfx {

struct ShapeStyle {
  const sf::Texture* texture = nullptr;
  sf::IntRect textureRect;
  sf::Color fillColor = sf::Color::White;
  sf::Color outlineColor = sf::Color::White;
  float outlineThickness = 0.f;

  void applyTo(sf::Shape& shape) const;
};

}  // namespace loki::gfx
