/*!
 * \file Camera.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "Camera.hpp"

namespace loki::window {

void Camera::setCenter(sf::Vector2f _center) {
  center = _center;
}
const sf::Vector2f& Camera::getCenter() const {
  return center;
}

void Camera::setZoom(float _zoom) {
  zoom = _zoom;
}
float Camera::getZoom() const {
  return zoom;
}

}  // namespace loki::window