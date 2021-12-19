/*!
 * \file RoundedRectangle.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics/Shape.hpp>

namespace loki::shapes {

class RoundedRectangle : public sf::Shape {
 public:
  explicit RoundedRectangle(sf::Vector2f size,
                            float borderRadius,
                            std::size_t borderPointCount = 7);
  ~RoundedRectangle() override = default;
  std::size_t getPointCount() const override;
  sf::Vector2f getPoint(std::size_t index) const override;

 private:
  sf::Vector2f getQuadrantOrigin(std::size_t quadrant) const;

 private:
  sf::Vector2f size;
  float borderRadius;
  std::size_t borderPointCount;
};

}  // namespace loki::shapes
