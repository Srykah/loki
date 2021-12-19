/*!
 * \file TextBox.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "TextBox.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <loki/core/utils/IterAdapters.hpp>

namespace loki::gui {

TextBox::TextBox(unsigned int lineCount,
                 styles::TextStyle textStyle,
                 std::unique_ptr<AbstractFrame> frame)
    : lineCount(lineCount), textStyle(textStyle), frame(std::move(frame)) {}

void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(*frame, states);
  for (const auto& line : lines) {
    target.draw(line, states);
  }
}

bool TextBox::hasEnded() const {
  return true;
}

bool TextBox::canFitInLine(const sf::String& string, unsigned int line) const {
  sf::Text testText;
  textStyle.applyTo(testText);
  testText.setString(string);
  return testText.getLocalBounds().width < frame->getInternalBounds().width;
}

size_t TextBox::getLineCount() const {
  return lineCount;
}

void TextBox::setLines(std::vector<sf::String> lineData) {
  // todo check size
  clear();
  for (auto&& [i, string] : loki::common::enumerate(lineData)) {
    lines.emplace_back(sf::Text{});
    textStyle.applyTo(lines.back());
    lines.back().setPosition(
        {frame->getInternalBounds().left,
         frame->getInternalBounds().top + textStyle.lineSpacing.value_or(1.f) * float(textStyle.characterSize.value_or(30.f)) * i});
    lines.back().setString(lineData[i]);
  }
}

void TextBox::clear() {
  lines.clear();
}

}  // namespace loki::gui
