/*!
 * \file AnimatedText.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "AnnotatedText.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace loki::text {

void AnnotatedText::setAnnotatedString(const AnnotatedString& annotatedString) {
  sf::Vector2f position;
  for (const auto& [str, style] : annotatedString) {
  }
}

void AnnotatedText::update(sf::Time delta) {}

void AnnotatedText::draw(sf::RenderTarget& target,
                        sf::RenderStates states) const {
  states.transform *= getTransform();
  for (const auto& block : blocks) {
    target.draw(block, states);
  }
}

void AnnotatedText::skip() {}

}
