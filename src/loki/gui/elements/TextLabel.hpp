#pragma once

#include "loki/graphics/text/AnnotatedText.hpp"
#include "loki/gui/Widget.hpp"

namespace loki::gui {

class TextLabel : public Widget {
 public:
  explicit TextLabel(const std::string& str);
  ~TextLabel() override = default;

  void draw(sf::RenderTarget& target,
            sf::RenderStates states = {}) const override {}

 private:
  gfx::AnnotatedText text;
};

}  // namespace loki::gui