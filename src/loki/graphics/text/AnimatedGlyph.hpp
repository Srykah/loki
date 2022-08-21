#pragma once

#include <SFML/Graphics/Glyph.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <loki/core/utils/VertexArrayIterator.hpp>
#include <loki/graphics/anim/ShapeAnimator.hpp>
#include "loki/graphics/text/AnimatedTextStyle.hpp"

namespace loki::gfx {

class AnimatedGlyph : public sf::Transformable {
 public:
  AnimatedGlyph(sf::VertexArray& va,
                std::size_t index,
                const sf::Glyph& glyph,
                const AnimatedTextStyle& style,
                float x);

  void setTime(sf::Time time);
  void end();

 private:
  enum State { APPEAR, IDLE, DISAPPEAR };

  void initAnim();
  void initTexRect();
  void updateVertices();

  friend gfx::ShapeAnimator<AnimatedGlyph>;
  void setColor(sf::Color color);
  sf::Color getColor() const;

 private:
  sf::VertexArray& va;
  std::size_t index = 0;
  const sf::Glyph& glyph;
  const AnimatedTextStyle& style;
  float x = 0.f;
  std::optional<gfx::ShapeAnimator<AnimatedGlyph>> anim;
  State state;
};

}  // namespace loki::text::impl
