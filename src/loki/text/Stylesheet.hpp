/*!
 * \file Stylesheet.hpp.h
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <filesystem>
#include <nlohmann/json.hpp>
#include "AnimatedTextStyle.hpp"

namespace loki::text {

class Stylesheet {
 public:
  void load(std::filesystem::path path);
  void load(nlohmann::json data);

  void setDefault(AnimatedTextStyle defaultStyle);

  const AnimatedTextStyle& getStyle(std::string styleName) const;

 private:
  AnimatedTextStyle defaultStyle;
  std::map<std::string, AnimatedTextStyle> styles;
};

}  // namespace loki::text
