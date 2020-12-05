/*!
 * \file TextStyle.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics/Text.hpp>

namespace loki::styles {

struct TextStyle {
  unsigned int characterSize = 30u;
  sf::Text::Style characterStyle = sf::Text::Style::Regular;
  sf::Color fillColor = sf::Color::White;
  sf::Font* font = nullptr;
  float letterSpacing = 1.f;
  float lineSpacing = 1.f;
  sf::Color outlineColor = sf::Color::Black;
  float outlineThickness = 0.f;

  TextStyle& withCharacterSize(unsigned int characterSize);
  TextStyle& withCharacterStyle(sf::Text::Style characterStyle);
  TextStyle& withFillColor(sf::Color fillColor);
  TextStyle& withFont(sf::Font* font);
  TextStyle& withLetterSpacing(float letterSpacing);
  TextStyle& withLineSpacing(float lineSpacing);
  TextStyle& withOutlineColor(sf::Color outlineColor);
  TextStyle& withOutlineThickness(float outlineThickness);

  void applyTo(sf::Text& text) const;
};

}  // namespace loki::gui