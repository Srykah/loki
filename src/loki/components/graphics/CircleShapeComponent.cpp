#include "CircleShapeComponent.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include <loki/system/ecs/Actor.hpp>

namespace loki::components {

CircleShapeComponent::CircleShapeComponent() {
  shape.setRadius(30.f);
  shape.setFillColor(sf::Color::Green);
}

void CircleShapeComponent::update(sf::Time dt) {}

system::DrawOrder CircleShapeComponent::getDrawOrder() const {
  return {};
}

void CircleShapeComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getActor().getTransform();
  target.draw(shape, states);
}

}  // namespace loki::components
