#pragma once

#include <loki/system/render/DrawOrder.hpp>

namespace loki::system {

class Drawable {
 public:
  [[nodiscard]] virtual DrawOrder getDrawOrder() const = 0;
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

class DebugDrawable {
 public:
  [[nodiscard]] virtual DrawOrder getDebugDrawOrder() const = 0;
  virtual void debugDraw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

}  // namespace loki::system