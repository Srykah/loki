/*!
 * \file AbstractFrame.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace loki::gui {

class AbstractFrame : public sf::Drawable, public sf::Transformable {
 public:
  virtual sf::FloatRect getInternalBounds() const = 0;
};

}  // namespace loki::gui
