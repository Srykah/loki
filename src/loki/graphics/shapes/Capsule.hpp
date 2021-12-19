/*!
 * \file Capsule.hpp.h
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics/Shape.hpp>

namespace loki::shapes {

class Capsule : public sf::Shape {
 public:
  explicit Capsule(sf::Vector2f size, std::size_t borderPointCount = 15);
  ~Capsule() override = default;
  std::size_t getPointCount() const override;
  sf::Vector2f getPoint(std::size_t index) const override;

 private:
  sf::Vector2f size;
  std::size_t borderPointCount;
};

}
