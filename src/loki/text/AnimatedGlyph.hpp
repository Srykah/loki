/*!
 * \file AnimatedGlyph.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace loki::text {

class AnimatedGlyph : public sf::Drawable, public sf::Transformable {
 public:
  AnimatedGlyph(sf::Uint32 codePoint, AnimatedTextStyle style);

  void update()
  
 private:
  sf::Uint32 codePoint;

};

}
