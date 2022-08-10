/*!
* \file Camera.hpp
* \author Srykah
* \copyright GNU GPL v3.0
*/
#pragma once

#include <SFML/System/Vector2.hpp>

namespace loki::window {

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

}