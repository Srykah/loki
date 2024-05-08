#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Time.hpp>

#include <loki/core/reflection/classMacros.hpp>
#include <loki/system/ecs/DrawableComponent.hpp>

namespace loki::components {

class CircleShapeComponent final : public system::DrawableComponent {
 public:
  CircleShapeComponent();

  [[nodiscard]] system::DrawOrder getDrawOrder() const override;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  sf::Time cumulatedTime;
  sf::CircleShape shape;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(CircleShapeComponent)
};

}  // namespace loki::components

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::Component, loki::components::CircleShapeComponent)
LOKI_REFLECTION_CLASS_END_RTTI(loki::components::CircleShapeComponent)
