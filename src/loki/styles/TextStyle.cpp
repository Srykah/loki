/*!
 * \file TextStyle.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "TextStyle.hpp"

namespace loki::styles {

TextStyle& TextStyle::withCharacterSize(unsigned int characterSize) {
  this->characterSize = characterSize;
  return *this;
}

TextStyle& TextStyle::withCharacterStyle(sf::Text::Style characterStyle) {
  this->characterStyle = characterStyle;
  return *this;
}

TextStyle& TextStyle::withFillColor(sf::Color fillColor) {
  this->fillColor = fillColor;
  return *this;
}

TextStyle& TextStyle::withFont(sf::Font* font) {
  this->font = font;
  return *this;
}

TextStyle& TextStyle::withLetterSpacing(float letterSpacing) {
  this->letterSpacing = letterSpacing;
  return *this;
}

TextStyle& TextStyle::withLineSpacing(float lineSpacing) {
  this->lineSpacing = lineSpacing;
  return *this;
}

TextStyle& TextStyle::withOutlineColor(sf::Color outlineColor) {
  this->outlineColor = outlineColor;
  return *this;
}

TextStyle& TextStyle::withOutlineThickness(float outlineThickness) {
  this->outlineThickness = outlineThickness;
  return *this;
}

void TextStyle::applyTo(sf::Text& text) const {
  text.setCharacterSize(characterSize);
  text.setStyle(characterStyle);
  text.setFillColor(fillColor);
  if (font) {
    text.setFont(*font);
  }
  text.setLetterSpacing(letterSpacing);
  text.setLineSpacing(lineSpacing);
  text.setOutlineColor(outlineColor);
  text.setOutlineThickness(outlineThickness);
}

}