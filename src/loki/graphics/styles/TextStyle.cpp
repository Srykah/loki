#include "TextStyle.hpp"

namespace loki::graphics {

TextStyle TextStyle::fromDefaults() {
  static const loki::graphics::TextStyle Defaults{30u,
                                             sf::Text::Style::Regular,
                                             sf::Color::White,
                                             nullptr,
                                             1.f,
                                             1.f,
                                             sf::Color::Black,
                                             0.f};
  return Defaults;
}

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
  if (characterSize.has_value()) {
    text.setCharacterSize(*characterSize);
  }
  if (characterStyle.has_value()) {
    text.setStyle(*characterStyle);
  }
  if (fillColor.has_value()) {
    text.setFillColor(*fillColor);
  }
  if (font.has_value() && *font) {
    text.setFont(**font);
  }
  if (letterSpacing.has_value()) {
    text.setLetterSpacing(*letterSpacing);
  }
  if (lineSpacing.has_value()) {
    text.setLineSpacing(*lineSpacing);
  }
  if (outlineColor.has_value()) {
    text.setOutlineColor(*outlineColor);
  }
  if (outlineThickness.has_value()) {
    text.setOutlineThickness(*outlineThickness);
  }
}

float TextStyle::getSpaceWidth() const {
  if (!font || !*font) {
    return 0;
  }
  return (*font)
      ->getGlyph(' ', characterSize.value_or(30u),
                 characterStyle.value_or(sf::Text::Regular) & sf::Text::Bold,
                 outlineThickness.value_or(0.f))
      .advance;
}

float TextStyle::getLineOffset() const {
  return characterSize.value_or(30u) * lineSpacing.value_or(1.f);
}

TextStyle& TextStyle::overrideWith(const TextStyle& other) {
  if (other.characterSize.has_value()) {
    characterSize = *other.characterSize;
  }
  if (other.characterStyle.has_value()) {
    characterStyle = *other.characterStyle;
  }
  if (other.fillColor.has_value()) {
    fillColor = *other.fillColor;
  }
  if (other.font.has_value() && other.font.value() != nullptr) {
    font = *other.font;
  }
  if (other.letterSpacing.has_value()) {
    letterSpacing = *other.letterSpacing;
  }
  if (other.lineSpacing.has_value()) {
    lineSpacing = *other.lineSpacing;
  }
  if (other.outlineColor.has_value()) {
    outlineColor = *other.outlineColor;
  }
  if (other.outlineThickness.has_value()) {
    outlineThickness = *other.outlineThickness;
  }
  return *this;
}

TextStyle TextStyle::cloneAndOverrideWith(const TextStyle& other) const {
  return TextStyle(*this).overrideWith(other);
}

}  // namespace loki::graphics
