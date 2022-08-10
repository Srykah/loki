/*!
 * \file AnimatedText.cpp.c
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "AnimatedText.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <loki/core/utils/IterAdapters.hpp>

namespace loki::text {

AnimatedText::AnimatedText(const std::string& string, AnimatedTextStyle style)
    : style(std::move(style)), vertices(sf::Triangles) {
  init(string);
}

void AnimatedText::update(sf::Time delta) {
  elapsedTime += delta;
  for (auto& glyph : glyphs) {
    glyph.setTime(elapsedTime);
  }
#if 0
  for (auto&& [i, glyph] : enumerate(glyphs)) {
    if (style.appear.has_value()) {
      sf::Time startingPoint = float(i) * style.appear->dt;
      if (skippingMoment != sf::Time::Zero) {
        startingPoint = std::min(startingPoint, skippingMoment);
      }
      if (elapsedTime - startingPoint <= style.appear->getDuration()) {
        glyph.updateVertices(
            style.appear->getTransform(elapsedTime - startingPoint),
            style.appear->getColor(elapsedTime - startingPoint));
        continue;
      }
    }
    if (style.animation.has_value()) {
      sf::Time startingPoint = float(i) * style.animation->dt;
      glyph.updateVertices(
          style.animation->getTransform(elapsedTime - startingPoint),
          style.animation->getColor(elapsedTime - startingPoint));
    }
  }
#endif
}

void AnimatedText::draw(sf::RenderTarget& target,
                        sf::RenderStates states) const {
  states.transform *= getTransform();
  states.texture = &style.font.value()->getTexture(style.characterSize.value());
  target.draw(vertices, states);
}

void AnimatedText::skip() {
  if (!style.appear) {
    return;
  }
  auto skippingMoment =
      style.appear->duration + static_cast<float>(glyphs.size() - 1) * style.dt;
  if (elapsedTime > skippingMoment) {
    return;
  }
  elapsedTime = skippingMoment;
}

void AnimatedText::init(const std::string& str) {
  auto string = sf::String::fromUtf8(str.begin(), str.end());
  auto& font = *style.font.value();
  auto charSize = style.characterSize.value_or(30);
  bool isBold =
      style.characterStyle.value_or(sf::Text::Regular) | sf::Text::Bold;
  float x = 0.f;
  sf::Uint32 lastChar;
  bool first = true;
  for (std::size_t i = 0; i < string.getSize(); ++i) {
    const auto& c = string[i];
    if (first) {
      first = false;
    } else {
      x += font.getKerning(lastChar, c, charSize);
    }
    lastChar = c;
    const auto glyph = font.getGlyph(c, charSize, isBold);
    vertices.resize(vertices.getVertexCount() + 6);
    glyphs.emplace_back(vertices, i, glyph, style, x);
    x += glyph.advance;
  }
}

bool AnimatedText::hasFinishedAppearing() const {
  if (isEnding)
    return true;
  if (style.appear) {
    return elapsedTime >= style.appear->duration +
                              static_cast<float>(glyphs.size() - 1) * style.dt;
  }
  return true;
}

sf::FloatRect AnimatedText::getLocalBounds() const {
  return {};  // todo todo todo
}

void AnimatedText::end() {
  isEnding = true;
  elapsedTime = sf::Time::Zero;
}

}  // namespace loki::text
