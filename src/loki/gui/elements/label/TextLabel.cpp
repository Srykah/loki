/*!
 * \file TextLabel.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "TextLabel.hpp"

#include <loki/graphics/text/AnnotatedStringEngine.hpp>

namespace loki::gui {

TextLabel::TextLabel(const std::string& str) {
  text::AnnotatedStringEngine engine{{}};
  text.setAnnotatedString(engine.parseAnnotatedString(str));
}

}  // namespace loki::gui
