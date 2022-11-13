#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <loki/core/utils/Memory.hpp>

namespace loki::system {

class SceneElement : public sf::Drawable {
 public:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override{};

  [[nodiscard]] int getLayerId() const { return layerId; }
  [[nodiscard]] int getZIndex() const { return zIndex; }

 private:
  int layerId = 0;
  int zIndex = 0;
};

}  // namespace loki::system