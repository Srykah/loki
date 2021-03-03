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
#include "AnimatedGlyph.hpp"
#include "Stylesheet.hpp"

namespace loki::text {

class AnimatedText : public sf::Drawable, public sf::Transformable {
 public:
  using FontGetter = std::function<sf::Font&(std::string)>;

 public:
  AnimatedText(const sf::String& string, const Stylesheet& stylesheet, const FontGetter& fontGetter);

  void update(sf::Time delta);
  void draw(sf::RenderTarget& target,
            sf::RenderStates states = sf::RenderStates()) const override;

  void skip();

 private:
  sf::String string;
  const Stylesheet& stylesheet;
  const FontGetter& fontGetter;
  sf::VertexArray vertices;

  void init();
};

}  // namespace loki::text
