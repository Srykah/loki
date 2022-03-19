/*!
 * \file TextStyle.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics/Text.hpp>
#include <nlohmann/json.hpp>
#include <optional>

namespace loki::styles {

using FontGetter = std::function<sf::Font&(std::string)>;

struct TextStyle {
  std::optional<unsigned int> characterSize;
  std::optional<sf::Text::Style> characterStyle;
  std::optional<sf::Color> fillColor;
  std::optional<sf::Font*> font;
  std::optional<float> letterSpacing;
  std::optional<float> lineSpacing;
  std::optional<sf::Color> outlineColor;
  std::optional<float> outlineThickness;

  static TextStyle fromDefaults();

  TextStyle& withCharacterSize(unsigned int characterSize);
  TextStyle& withCharacterStyle(sf::Text::Style characterStyle);
  TextStyle& withFillColor(sf::Color fillColor);
  TextStyle& withFont(sf::Font* font);
  TextStyle& withLetterSpacing(float letterSpacing);
  TextStyle& withLineSpacing(float lineSpacing);
  TextStyle& withOutlineColor(sf::Color outlineColor);
  TextStyle& withOutlineThickness(float outlineThickness);

  void load(const nlohmann::json& data, const FontGetter& fontGetter);
  void applyTo(sf::Text& text) const;

  [[nodiscard]] float getSpaceWidth() const;
  [[nodiscard]] float getLineOffset() const;

  TextStyle& overrideWith(const TextStyle& other);
  TextStyle cloneAndOverrideWith(const TextStyle& other) const;
};

}  // namespace loki::styles
