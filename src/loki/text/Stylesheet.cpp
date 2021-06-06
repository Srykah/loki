/*!
 * \file Stylesheet.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "Stylesheet.hpp"

namespace loki::text {

const AnimatedTextStyle& Stylesheet::getDefaultStyle() const {
  return styles.at(".default");
}
AnimatedTextStyle Stylesheet::getNewStyleFromBase(
    const AnimatedTextStyle& base,
    const std::vector<sf::String>& styleNames) const {
  AnimatedTextStyle copy(base);
  for (const auto& styleName : styleNames) {
    copy.overrideWith(getStyle(styleName));
  }
  return copy;
}

const AnimatedTextStyle& Stylesheet::getStyle(const sf::String& styleName) const {
  return styles.at(styleName);
}

void Stylesheet::setStyle(const sf::String& styleName,
                          const AnimatedTextStyle& defaultStyle) {
  styles.emplace(styleName, defaultStyle);
}

void Stylesheet::setDefaultStyle(const AnimatedTextStyle& defaultStyle) {
  setStyle(".default", defaultStyle);
}

}
