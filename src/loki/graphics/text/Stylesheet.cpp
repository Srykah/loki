/*!
 * \file Stylesheet.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "Stylesheet.hpp"

namespace loki::text {

const AnimatedTextStyle& Stylesheet::getStyle(
    const std::string& styleName) const {
  return styles.at(styleName);
}

const AnimatedTextStyle& Stylesheet::getDefaultStyle() const {
  return getStyle(".default");
}

void Stylesheet::setStyle(const std::string& styleName,
                          const AnimatedTextStyle& style) {
  styles.emplace(styleName, style);
}

void Stylesheet::setDefaultStyle(const AnimatedTextStyle& defaultStyle) {
  setStyle(".default", defaultStyle);
}

AnimatedTextStyle Stylesheet::getNewStyleFromBase(
    AnimatedTextStyle base,
    const std::vector<std::string>& styleNames) const {
  for (const auto& styleName : styleNames) {
    base.overrideWith(getStyle(styleName));
  }
  return base;
}

}  // namespace loki::text
