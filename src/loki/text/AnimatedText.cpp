/*!
 * \file AnimatedText.cpp.c
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "AnimatedText.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace loki::text {

AnimatedText::AnimatedText(const sf::String& string, const Stylesheet& stylesheet, const AnimatedText::FontGetter& fontGetter)
: string(string)
, stylesheet(stylesheet)
, fontGetter(fontGetter)
, vertices(sf::Triangles) {
  init();
}

void AnimatedText::update(sf::Time delta) {}

void AnimatedText::draw(sf::RenderTarget& target,
                        sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(vertices, states);
}

void AnimatedText::skip() {}

void AnimatedText::init() {
  for (const auto& c : string) {

  }
}

}
