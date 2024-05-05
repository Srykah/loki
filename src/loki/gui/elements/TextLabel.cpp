#include "TextLabel.hpp"

#include <loki/graphics/text/AnnotatedStringEngine.hpp>

namespace loki::gui {

TextLabel::TextLabel(const std::string& str) {
  graphics::AnnotatedStringEngine engine{{}};
  text.setAnnotatedString(engine.parseAnnotatedString(str));
}

}  // namespace loki::gui
