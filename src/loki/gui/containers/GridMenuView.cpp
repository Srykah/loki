/*!
 * \file GridMenuView.cpp.cc
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "GridMenuView.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

#if 0
namespace loki::gui {

GridMenuView::GridMenuView(sf::Vector2f frameSize,
                           float padding,
                           const styles::ShapeStyle& frameStyle,
                           const styles::TextStyle& textStyle)
    : frame(frameSize),
      padding(padding),
      frameStyle(frameStyle),
      textStyle(textStyle) {
  frameStyle.applyTo(frame);
}

void GridMenuView::draw(sf::RenderTarget& target,
                        sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(frame, states);
}

void GridMenuView::update(sf::Time delta) {}

void GridMenuView::setItem(sf::Vector2u coords, const std::string& text) {}

}  // namespace loki::gui
#endif
