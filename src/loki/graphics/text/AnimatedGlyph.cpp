#include "AnimatedGlyph.hpp"

namespace loki::graphics {

AnimatedGlyph::AnimatedGlyph(sf::VertexArray& va,
                             std::size_t index,
                             const sf::Glyph& glyph,
                             const AnimatedTextStyle& style,
                             float x)
    : va(va), index(index), glyph(glyph), style(style), x(x) {
  initTexRect();
  initAnim();
  animator.setAnimated(*this);
  if (style.appear) {
    animator.setData(*style.appear);
    animator.start();
    state = APPEAR;
  } else {
    if (style.idle) {
      animator.setData(*style.idle);
      animator.start();
    }
    state = IDLE;
  }
}

void AnimatedGlyph::initAnim() {
  auto xCenter = glyph.bounds.left + 0.5f * glyph.bounds.width;
  auto yCenter = glyph.bounds.top + 0.5f * glyph.bounds.height;
  setOrigin(xCenter, yCenter);
  setPosition(x + xCenter, yCenter);
  setRotation(0.f);
  setScale(1.f, 1.f);
  setColor(style.fillColor.value_or(sf::Color::White));
}

void AnimatedGlyph::updateVertices() {
  float padding = 1.0;
  float shear = (style.characterStyle.value_or(sf::Text::Regular) & sf::Text::Italic) ? 0.209f : 0.f;

  float left = glyph.bounds.left - padding;
  float top = glyph.bounds.top - padding;
  float right = glyph.bounds.left + glyph.bounds.width + padding;
  float bottom = glyph.bounds.top + glyph.bounds.height + padding;

  /*    0 - 1,4
   *    | / |
   *  2,3 - 5
   */
  va[index * 6 + 0].position = getTransform().transformPoint(sf::Vector2f(left - shear * top, top));
  va[index * 6 + 1].position = getTransform().transformPoint(sf::Vector2f(right - shear * top, top));
  va[index * 6 + 2].position = getTransform().transformPoint(sf::Vector2f(left - shear * bottom, bottom));
  va[index * 6 + 3].position = va[index * 6 + 2].position;
  va[index * 6 + 4].position = va[index * 6 + 1].position;
  va[index * 6 + 5].position = getTransform().transformPoint(sf::Vector2f(right - shear * bottom, bottom));
}

void AnimatedGlyph::initTexRect() {
  float padding = 1.0;

  float u1 = static_cast<float>(glyph.textureRect.left) - padding;
  float v1 = static_cast<float>(glyph.textureRect.top) - padding;
  float u2 = static_cast<float>(glyph.textureRect.left + glyph.textureRect.width) + padding;
  float v2 = static_cast<float>(glyph.textureRect.top + glyph.textureRect.height) + padding;

  /*    0 - 1,4
   *    | / |
   *  2,3 - 5
   */
  va[index * 6 + 0].texCoords = sf::Vector2f(u1, v1);
  va[index * 6 + 1].texCoords = sf::Vector2f(u2, v1);
  va[index * 6 + 2].texCoords = sf::Vector2f(u1, v2);
  va[index * 6 + 3].texCoords = sf::Vector2f(u1, v2);
  va[index * 6 + 4].texCoords = sf::Vector2f(u2, v1);
  va[index * 6 + 5].texCoords = sf::Vector2f(u2, v2);
}

void AnimatedGlyph::setTime(sf::Time time) {
  time -= static_cast<float>(index) * style.dt;
  if (state == APPEAR) {
    if (time < sf::Time::Zero) {
      return;
    }
    if (time >= style.appear->duration) {
      state = IDLE;
      if (style.idle) {
        initAnim();

        animator.setData(*style.idle);
        animator.start();
      }
      // fallthrough to IDLE case
    }
  }
  if (state == IDLE && style.appear) {
    time -= style.appear->duration;
  }
  if (state == DISAPPEAR && time < sf::Time::Zero) {
    return;
  }
  if (!animator.isPaused() && !animator.hasEnded()) {
    animator.setTime(time);
    updateVertices();
  }
}

void AnimatedGlyph::end() {
  state = DISAPPEAR;
  if (style.disappear) {
    initAnim();
    animator.setData(*style.disappear);
    animator.start();
  }
}

void AnimatedGlyph::setColor(sf::Color color) {
  for (int i{0}; i < 6; ++i) {
    va[index * 6 + i].color = color;
  }
}

sf::Color AnimatedGlyph::getColor() const {
  return style.fillColor.value_or(sf::Color::White);
}

}  // namespace loki::graphics
