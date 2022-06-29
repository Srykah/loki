/*!
 * \file RoundedRectangle.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "RoundedRectangle.hpp"
#include <cmath>
#include <numbers>

namespace loki::shapes {

RoundedRectangle::RoundedRectangle(sf::Vector2f size,
                                   float borderRadius,
                                   std::size_t borderPointCount)
    : size(size),
      borderRadius(borderRadius),
      borderPointCount(borderPointCount) {
  update();
}

std::size_t RoundedRectangle::getPointCount() const {
  if (borderRadius == 0.f) {
    // degenerate case
    return 4;
  }
  return borderPointCount * 4;
}

sf::Vector2f RoundedRectangle::getPoint(std::size_t index) const {
  if (borderRadius == 0.f) {
    // degenerate case
    return getQuadrantOrigin(index);
  }
  auto quadrant = index / borderPointCount;
  auto origin = getQuadrantOrigin(quadrant);
  index -= quadrant;
  float angle = 0.5f * index * std::numbers::pi / (borderPointCount - 1);
  return origin + borderRadius * sf::Vector2f{std::cos(angle), std::sin(angle)};
}

sf::Vector2f RoundedRectangle::getQuadrantOrigin(std::size_t quadrant) const {
  if (quadrant == 0) {
    // bottom-right
    return size - sf::Vector2f{borderRadius, borderRadius};
  } else if (quadrant == 1) {
    // bottom-left
    return sf::Vector2f{borderRadius, size.y - borderRadius};
  } else if (quadrant == 2) {
    // top-left
    return sf::Vector2f{borderRadius, borderRadius};
  } else /* if (quadrant == 3) */ {
    // top-right
    return sf::Vector2f{size.x - borderRadius, borderRadius};
  }
}

}  // namespace loki::shapes
