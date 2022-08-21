#include "TextLabel.hpp"

#include "loki/graphics/text/AnnotatedStringEngine.hpp"

namespace loki::gui {

TextLabel::TextLabel(const std::string& str) {
  gfx::AnnotatedStringEngine engine{{}};
  text.setAnnotatedString(engine.parseAnnotatedString(str));
}

}  // namespace loki::gui
