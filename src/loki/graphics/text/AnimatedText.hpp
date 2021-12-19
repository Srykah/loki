/*!
 * \file AnimatedText.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>
#include "Stylesheet.hpp"
#include "impl/AnimatedGlyph.hpp"

namespace loki::text {

class AnimatedText : public sf::Drawable, public sf::Transformable {
 public:
  AnimatedText(const sf::String& string, const AnimatedTextStyle& style);
  ~AnimatedText() = default;

  void update(sf::Time delta);
  void draw(sf::RenderTarget& target,
            sf::RenderStates states = sf::RenderStates()) const override;

  void skip();

  sf::FloatRect getLocalBounds();

 private:
  sf::Time skippingMoment;
  sf::Time elapsedTime;
  sf::String string;
  const AnimatedTextStyle& style;
  sf::VertexArray vertices;
  std::vector<impl::AnimatedGlyph> glyphs;

  void init();
};

}  // namespace loki::text
