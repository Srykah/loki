/*!
 * \file Stylesheet.hpp.h
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <map>
#include <string>
#include "TextBoxStyle.hpp"

namespace loki::gui {

class Stylesheet {
  std::map<std::string, TextBoxStyle> textBoxStyles;
};

}  // namespace loki::gui
