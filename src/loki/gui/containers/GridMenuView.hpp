#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Time.hpp>

#include "loki/graphics/styles/ShapeStyle.hpp"
#include "loki/graphics/styles/TextStyle.hpp"
#include "loki/gui/Widget.hpp"

#if 0
namespace loki::gui {

class GridMenuView : public AWidgetView {
 public:
  GridMenuView(sf::Vector2f size,
               float padding,
               const gfx::ShapeStyle& frameStyle,
               const gfx::TextStyle& textStyle);

  void setItem(sf::Vector2u coords, const std::string& text);

  void draw(sf::RenderTarget& target,
            sf::RenderStates core = {}) const override;

  void update(sf::Time delta);

 protected:
  void hideImpl() override {}
  void unhideImpl() override {}
  void enableImpl() override {}
  void disableImpl() override {}
  void focusImpl() override {}
  void unfocusImpl() override {}
  void activateImpl() override {}
  void deactivateImpl() override {}

 private:
  sf::RectangleShape frame;
  float padding;
  const gfx::ShapeStyle& frameStyle;
  const gfx::TextStyle& textStyle;
};

}  // namespace loki::gui
#endif
