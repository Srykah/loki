#pragma once

#include <SFML/System/Vector2.hpp>

namespace loki::system {

class Camera {
 public:
  void setCenter(sf::Vector2f center);
  [[nodiscard]] const sf::Vector2f& getCenter() const;

  void setZoom(float zoom);
  [[nodiscard]] float getZoom() const;

 private:
  sf::Vector2f center;
  float zoom = 1.f;
};

}  // namespace loki::system