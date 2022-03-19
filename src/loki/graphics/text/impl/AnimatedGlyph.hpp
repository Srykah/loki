/*!
 * \file AnimatedGlyph.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics/Glyph.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <loki/core/utils/VertexArrayIterator.hpp>
#include "loki/graphics/text/AnimatedTextStyle.hpp"

namespace loki::text::impl {

class AnimatedGlyph : public sf::Transformable {
 public:
  AnimatedGlyph(const sf::Glyph& glyph,
                const AnimatedTextStyle& style,
                VertexArrayIterator vaIt,
                float x);

  void updateVertices(const sf::Transform& transform,
                      const sf::Color& color);

 private:
  void initBasePos(const sf::Glyph& glyph,
                   float x);
  void initTexRect(const sf::Glyph& glyph);

 private:
  VertexArrayIterator vaIt;
  const AnimatedTextStyle& style;
  sf::Vector2f basePos[6];
};

}
