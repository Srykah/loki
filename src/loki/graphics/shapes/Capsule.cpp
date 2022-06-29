/*!
 * \file Capsule.cpp.c
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "Capsule.hpp"
#include <cmath>
#include <numbers>

namespace loki::shapes {

Capsule::Capsule(sf::Vector2f size, std::size_t borderPointCount)
    : size(size), borderPointCount(borderPointCount) {
  update();
}

std::size_t loki::shapes::Capsule::getPointCount() const {
  return borderPointCount * 2;
}

sf::Vector2f loki::shapes::Capsule::getPoint(std::size_t index) const {
  float radius = std::min(size.x, size.y) / 2.f;
  sf::Vector2f origin;
  if (index < borderPointCount) {
    origin = size - sf::Vector2f{radius, radius};
  } else {
    origin = sf::Vector2f{radius, radius};
    --index;
  }
  float angle = index * std::numbers::pi / (borderPointCount - 1);
  if (size.x >= size.y) {
    angle -= std::numbers::pi / 2.f;
  }
  return origin + radius * sf::Vector2f{std::cos(angle), std::sin(angle)};
}

}  // namespace loki::shapes
