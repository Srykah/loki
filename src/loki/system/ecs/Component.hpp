#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>
#include "Actor.hpp"

namespace loki::system {

class Component {
 public:
  virtual ~Component() = default;

  virtual void update(sf::Time delta){};

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {};
  virtual void drawOnLayer(int layer,
                           sf::RenderTarget& target,
                           sf::RenderStates states) const {};

 protected:
  /// Set to -1 to use drawOnLayer; set to -2 to disable drawing entirely (which
  /// is the default). Avoid changing at runtime.
  void setDrawLayer(int layer);

 protected:
  Actor* actor = nullptr;
};

}  // namespace loki::system
