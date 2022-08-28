#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "loki/graphics/styles/TextStyle.hpp"

namespace loki::gui {

class TextList : public sf::Drawable, public sf::Transformable {
 public:
  explicit TextList(sf::Font& font);
  void setTextStyle(gfx::TextStyle textStyle);
  void setSpacing(float spacing);

  void draw(sf::RenderTarget& target,
            sf::RenderStates states = sf::RenderStates()) const override;

 private:
  gfx::TextStyle textStyle;
  float spacing;
  unsigned int selection;
  std::vector<sf::Text> items;
};

}  // namespace loki::gui
