#include "TextList.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace loki::gui {

TextList::TextList(sf::Font& font) {}

void TextList::setTextStyle(gfx::TextStyle _textStyle) {
  this->textStyle = _textStyle;
}

void TextList::setSpacing(float spacing) {}

void TextList::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  for (const auto& item : items) {
    target.draw(item, states);
  }
}

}  // namespace loki::gui