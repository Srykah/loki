#pragma once

#include <SFML/Graphics/Drawable.hpp>

#include "Component.hpp"

namespace loki::system {

struct DrawOrder {
  std::int32_t layer = 0;
  float priority = 0;

  auto operator<=>(const DrawOrder&) const = default;
};

class DrawableComponent : public Component, public sf::Drawable {
 public:
  [[nodiscard]] virtual DrawOrder getDrawOrder() const = 0;
};

}  // namespace loki::system