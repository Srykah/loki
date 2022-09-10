#pragma once

#include <memory>
#include <string>
#include <vector>

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include "loki/core/utils/Matrix.hpp"
#include "loki/gui/Widget.hpp"

namespace loki::gui {

class Grid : public Widget {
 public:
  explicit Grid(sf::Vector2u size);

  void setItem(sf::Vector2u coords, Widget::UPtr&& item);

  void update(sf::Time delta) override;

  void draw(sf::RenderTarget& target,
            sf::RenderStates states = {}) const override {}

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
  loki::core::Matrix<Widget::UPtr> items;
  unsigned int hovered = 0;
  unsigned int selected = -1;
};

}  // namespace loki::gui
