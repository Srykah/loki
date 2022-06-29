/*!
 * \file TextList.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "loki/graphics/styles/TextStyle.hpp"

namespace loki::gui {

class TextList : public sf::Drawable, public sf::Transformable {
 public:
  explicit TextList(sf::Font& font);
  void setTextStyle(styles::TextStyle textStyle);
  void setSpacing(float spacing);

  void draw(sf::RenderTarget& target,
            sf::RenderStates states = sf::RenderStates()) const override;

 private:
  styles::TextStyle textStyle;
  float spacing;
  unsigned int selection;
  std::vector<sf::Text> items;
};

}  // namespace loki::gui
