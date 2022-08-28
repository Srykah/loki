#pragma once

#include "loki/gui/Widget.hpp"

namespace loki::gui {

class Frame : public Widget {
 public:
  virtual sf::FloatRect getInternalBounds() const = 0;
};

}  // namespace loki::gui
