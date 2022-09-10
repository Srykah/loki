#include "RectangleShapeFrame.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace loki::gui {

RectangleShapeFrame::RectangleShapeFrame(sf::Vector2f size,
                                         float padding,
                                         const gfx::ShapeStyle& style)
    : padding(padding) {
  shape.setSize(size);
  style.applyTo(shape);
}

sf::FloatRect RectangleShapeFrame::getInternalBounds() const {
  return sf::FloatRect{padding, padding, shape.getSize().x - padding,
                       shape.getSize().y - padding};
}

void RectangleShapeFrame::draw(sf::RenderTarget& target,
                               sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(shape, states);
}

}  // namespace loki::gui
