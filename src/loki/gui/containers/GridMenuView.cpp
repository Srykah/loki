#include "GridMenuView.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#if 0
namespace loki::gui {

GridMenuView::GridMenuView(sf::Vector2f frameSize,
                           float padding,
                           const gfx::ShapeStyle& frameStyle,
                           const gfx::TextStyle& textStyle)
    : frame(frameSize),
      padding(padding),
      frameStyle(frameStyle),
      textStyle(textStyle) {
  frameStyle.applyTo(frame);
}

void GridMenuView::draw(sf::RenderTarget& target,
                        sf::RenderStates core) const {
  core.transform *= getTransform();
  target.draw(frame, core);
}

void GridMenuView::update(sf::Time delta) {}

void GridMenuView::setItem(sf::Vector2u coords, const std::string& text) {}

}  // namespace loki::gui
#endif
