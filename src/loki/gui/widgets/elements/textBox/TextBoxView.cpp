/*!
 * \file TextBox.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "TextBoxView.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include "loki/core/utils/IterAdapters.hpp"
#include "loki/graphics/text/AnnotatedStringEngine.hpp"

namespace loki::gui {

TextBoxView::TextBoxView(sf::Vector2f size,
                         float padding,
                         unsigned int lineCount,
                         const styles::ShapeStyle& frameStyle,
                         const text::Stylesheet& textStylesheet)
    : frame(size),
      padding(padding),
      lineCount(lineCount),
      textStylesheet(textStylesheet),
      frameStyle(frameStyle) {
  frameStyle.applyTo(frame);
}

void TextBoxView::draw(sf::RenderTarget& target,
                       sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(frame, states);
  for (const auto& line : lines) {
    for (const auto& word : line) {
      target.draw(word, states);
    }
  }
}

bool TextBoxView::hasAnimationStopped() const {
  return true;
}

bool TextBoxView::hasEnded() const {
  return true;
}

void TextBoxView::setAnnotatedString(const std::string& annotatedString) {
  const char DELIMS[] = " \n";
  const float LINE_OFFSET = textStylesheet.getDefaultStyle().getLineOffset();
  const float SPACE_WIDTH = textStylesheet.getDefaultStyle().getSpaceWidth();
  const float MAX_LINE_WIDTH = frame.getLocalBounds().width - 2 * padding;
  const float X_PADDING = frame.getLocalBounds().left + padding;
  const float Y_PADDING = frame.getLocalBounds().top + padding;

  auto parsedString = text::AnnotatedStringEngine(textStylesheet)
                          .parseAnnotatedString(annotatedString);

  std::vector<text::AnimatedText>* curLine;
  float curLineWidth;

  auto newline = [&]() {
    lines.emplace_back();
    curLine = &lines.back();
    curLineWidth = 0.f;
  };

  clear();
  newline();

  for (const auto& [part, style] : parsedString) {
    auto wordBegin = part.begin();
    while (wordBegin < part.end()) {
      auto wordEnd = std::find_first_of(wordBegin, part.end(),
                                        std::begin(DELIMS), std::end(DELIMS));

      if (wordBegin != wordEnd) {
        text::AnimatedText text{std::string{wordBegin, wordEnd}, style};
        float textWidth = text.getLocalBounds().width;

        if (curLineWidth + textWidth > MAX_LINE_WIDTH && !curLine->empty()) {
          newline();
        }

        text.setPosition(X_PADDING + curLineWidth,
                         Y_PADDING + LINE_OFFSET * (lines.size() - 1));
        curLine->emplace_back(std::move(text));
        curLineWidth += textWidth + SPACE_WIDTH;
      }

      if (wordEnd != part.end() && *wordEnd == '\n') {
        newline();
      }

      wordBegin = wordEnd + 1;
    }
  }

  while (lines.back().empty()) {
    lines.pop_back();
  }
  while (lines.front().empty()) {
    lines.erase(lines.begin());
  }
}

void TextBoxView::advance() {}

void TextBoxView::skipAnimation() {}

void TextBoxView::clear() {
  lines.clear();
}

}  // namespace loki::gui
