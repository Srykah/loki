/*!
 * \file AnimatedGlyph.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "AnimatedGlyph.hpp"

namespace loki::text::impl {

AnimatedGlyph::AnimatedGlyph(const sf::Glyph& glyph,
                             const AnimatedTextStyle& style,
                             VertexArrayIterator vaIt,
                             float x)
    : style(style), vaIt(vaIt) {
  initBasePos(glyph, x);
  initTexRect(glyph);
  if (style.appear.has_value()) {
    updateVertices(style.appear->getTransform(sf::Time::Zero),
                   style.appear->getColor(sf::Time::Zero));
  } else {
    updateVertices(sf::Transform::Identity, sf::Color::White);
  }
}

void AnimatedGlyph::initBasePos(const sf::Glyph& glyph, float x) {
  float padding = 1.0;
  float shear =
      (style.characterStyle.value_or(sf::Text::Regular) & sf::Text::Italic)
          ? 0.209f
          : 0.f;

  float left = glyph.bounds.left - padding;
  float top = glyph.bounds.top - padding;
  float right = glyph.bounds.left + glyph.bounds.width + padding;
  float bottom = glyph.bounds.top + glyph.bounds.height + padding;

  basePos[0] = sf::Vector2f(x + left - shear * top, top);
  basePos[1] = sf::Vector2f(x + right - shear * top, top);
  basePos[2] = sf::Vector2f(x + left - shear * bottom, bottom);
  basePos[3] = sf::Vector2f(x + left - shear * bottom, bottom);
  basePos[4] = sf::Vector2f(x + right - shear * top, top);
  basePos[5] = sf::Vector2f(x + right - shear * bottom, bottom);
}

void AnimatedGlyph::initTexRect(const sf::Glyph& glyph) {
  float padding = 1.0;

  float u1 = static_cast<float>(glyph.textureRect.left) - padding;
  float v1 = static_cast<float>(glyph.textureRect.top) - padding;
  float u2 =
      static_cast<float>(glyph.textureRect.left + glyph.textureRect.width) +
      padding;
  float v2 =
      static_cast<float>(glyph.textureRect.top + glyph.textureRect.height) +
      padding;

  (vaIt + 0)->texCoords = sf::Vector2f(u1, v1);
  (vaIt + 1)->texCoords = sf::Vector2f(u2, v1);
  (vaIt + 2)->texCoords = sf::Vector2f(u1, v2);
  (vaIt + 3)->texCoords = sf::Vector2f(u1, v2);
  (vaIt + 4)->texCoords = sf::Vector2f(u2, v1);
  (vaIt + 5)->texCoords = sf::Vector2f(u2, v2);
}

void AnimatedGlyph::updateVertices(const sf::Transform& transform,
                                   const sf::Color& _color) {
  for (int i{0}; i < 6; ++i) {
    (vaIt + i)->color = style.fillColor.value_or(sf::Color::White) * _color;
    (vaIt + i)->position = transform.transformPoint(basePos[i]);
  }
}

/*void AnimatedGlyph::update(sf::Time delta) {
  if (playing) {
    elapsedTime += delta;
    if (appearing && !disappearing && style.appear.has_value()) {
      const sf::Time& appearDuration = style.appear->getDuration();
      if (elapsedTime >= appearDuration) {
        updateVertices(
            style.appear->getTransform(appearDuration),
            style.appear->getColor(appearDuration));
        elapsedTime -= appearDuration;
        appearing = false;
      } else {
        updateVertices(
            style.appear->getTransform(elapsedTime),
            style.appear->getColor(elapsedTime));
      }
    }
    if (!appearing && !disappearing && style.animation.has_value()) {
      const sf::Time& animationDuration = style.animation->getDuration();
      for (elapsedTime += delta;
           elapsedTime >= animationDuration;
           elapsedTime -= animationDuration);
      updateVertices(
          style.animation->getTransform(elapsedTime),
          style.animation->getColor(elapsedTime));
    }
    if (disappearing && style.disappear.has_value()) {
      const sf::Time& disappearDuration = style.appear->getDuration();
      if (elapsedTime >= disappearDuration) {
        updateVertices(
            style.disappear->getTransform(disappearDuration),
            style.appear->getColor(disappearDuration));
        elapsedTime = sf::Time::Zero;
        playing = false;
      } else {
        updateVertices(
            style.disappear->getTransform(elapsedTime),
            style.disappear->getColor(elapsedTime));
      }
    }
  }
}

void AnimatedGlyph::appear() {
  appearing = true;
}

bool AnimatedGlyph::isAppearing() const {
  return appearing;
}*/

}  // namespace loki::text::impl
