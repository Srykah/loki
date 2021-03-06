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
#include "AnimatedText.hpp"
#include "Stylesheet.hpp"

namespace loki::text {

class AnnotatedText : public sf::Drawable, public sf::Transformable {
 public:
  AnnotatedText() = default;
  AnnotatedText(const sf::String& string, const Stylesheet& stylesheet);

  void setString(const sf::String& string, const Stylesheet& stylesheet);

  void update(sf::Time delta);
  void draw(sf::RenderTarget& target,
            sf::RenderStates states = sf::RenderStates()) const override;

  void skip();

 private:
  std::vector<AnimatedText> blocks;
  void closeBlock(sf::String::ConstIterator begin,
                  sf::String::ConstIterator end,
                  const AnimatedTextStyle& style,
                  sf::Vector2f& position);
};

}  // namespace loki::text
