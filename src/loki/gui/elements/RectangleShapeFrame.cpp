#include "RectangleShapeFrame.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace loki::gui {

RectangleShapeFrame::RectangleShapeFrame(sf::Vector2f size,
                                         float padding,
                                         const graphics::ShapeStyle& style)
    : padding(padding) {
  shape.setSize(size);
  style.applyTo(shape);
}

sf::FloatRect RectangleShapeFrame::getInternalBounds() const {
  const sf::Vector2f padding2d {padding, padding};
  return {padding2d, shape.getSize() - padding2d};
}

void RectangleShapeFrame::draw(sf::RenderTarget& target,
                               sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(shape, states);
}

}  // namespace loki::gui
