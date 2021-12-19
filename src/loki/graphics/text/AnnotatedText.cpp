/*!
 * \file AnimatedText.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "AnnotatedText.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace loki::text {

namespace {

const auto tokens = std::array { '\\', '[', ']' };
const auto styleModeTokens = std::array { ',', ':' };

}

AnnotatedText::AnnotatedText(const sf::String& string, const Stylesheet& stylesheet) {
  setString(string, stylesheet);
}

void AnnotatedText::setString(const sf::String& string, const Stylesheet& stylesheet) {
  sf::Vector2f position;
  std::vector<AnimatedTextStyle> styles(1, stylesheet.getDefaultStyle());
  auto it = string.begin();
  while (true) {
    auto nextToken = std::find_first_of(
        it,
        string.end(),
        tokens.begin(),
        tokens.end());
    while (nextToken != string.end() && *nextToken == '\\') {
      // ignore backslashes
      nextToken = std::find_first_of(
          nextToken + 2,
          string.end(),
          tokens.begin(),
          tokens.end());
    }
    // close block
    closeBlock(it, nextToken - (nextToken != string.end()), styles.back(), position);
    if (nextToken == string.end()) {
      // end processing
      break;
    }
    if (*nextToken == ']') {
      // pop style stack
      styles.pop_back();
    } else if (*nextToken == '[') {
      // push style
      std::vector<sf::String> newStyles;
      while (nextToken != string.end() && *nextToken != ':') {
        auto nextStyleModeToken = std::find_first_of(
            nextToken + 1,
            string.end(),
            styleModeTokens.begin(),
            styleModeTokens.end());
        if (nextStyleModeToken == string.end()) {
          // unexpected end, ignore
          break;
        }
        // get new style name
        const auto style = sf::String::fromUtf32(nextToken + 1, nextStyleModeToken - 1);
        if (!style.isEmpty()) {
          newStyles.emplace_back(style);
        }
        if (*nextStyleModeToken == ':') {
          // finished parsing style names : push resulting style to the stack
          styles.emplace_back(stylesheet.getNewStyleFromBase(styles.back(), newStyles));
        }
        nextToken = nextStyleModeToken;
      }
    }
    it = nextToken + 1;
  }
}

void AnnotatedText::update(sf::Time delta) {}

void AnnotatedText::draw(sf::RenderTarget& target,
                        sf::RenderStates states) const {
  states.transform *= getTransform();
  for (const auto& block : blocks) {
    target.draw(block, states);
  }
}

void AnnotatedText::skip() {}

void AnnotatedText::closeBlock(sf::String::ConstIterator begin,
                              sf::String::ConstIterator end,
                              const AnimatedTextStyle& style,
                              sf::Vector2f& position) {
  auto blockText = sf::String::fromUtf32(begin, end);
  for (const auto& token : tokens) {
    blockText.replace(sf::String('\\') + token, token);
  }
  blocks.emplace_back(blockText, style);
  blocks.back().setPosition(position);
  position.x += blocks.back().getLocalBounds().width + style.getSpaceWidth();
}

}
