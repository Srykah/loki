/*!
 * \file Stylesheet.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <filesystem>
#include <nlohmann/json.hpp>
#include <SFML/System/String.hpp>
#include "AnimatedTextStyle.hpp"

namespace loki::text {

class Stylesheet {
 public:
  void setStyle(sf::String styleName, const AnimatedTextStyle& defaultStyle);
  void setDefaultStyle(const AnimatedTextStyle& defaultStyle);
  [[nodiscard]] const AnimatedTextStyle& getStyle(const sf::String& styleName) const;
  [[nodiscard]] const AnimatedTextStyle& getDefaultStyle() const;

  [[nodiscard]] AnimatedTextStyle getNewStyleFromBase(
      const AnimatedTextStyle& base,
      const std::vector<sf::String>& styleNames) const;

 private:
  std::map<sf::String, AnimatedTextStyle> styles;
};

void from_json(const nlohmann::json& json, Stylesheet& ss);

}  // namespace loki::text
