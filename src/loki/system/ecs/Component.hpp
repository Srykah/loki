#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>

#include "Actor.hpp"

namespace loki::system {

class Component {
 public:
  virtual ~Component() = default;

  virtual void update(sf::Time delta){};

 protected:
  Actor* actor = nullptr;
};

}  // namespace loki::system
