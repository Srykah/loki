#pragma once

#include <queue>
#include <string>

#include "AnimatedTextStyle.hpp"
#include "Stylesheet.hpp"

namespace loki::gfx {

using AnnotatedString = std::vector<std::pair<std::string, AnimatedTextStyle>>;

class AnnotatedStringEngine {
 public:
  explicit AnnotatedStringEngine(const Stylesheet& stylesheet);
  AnnotatedString parseAnnotatedString(const std::string& annotatedString);

 private:
  void readText();
  void readStyle();

 private:
  const Stylesheet& stylesheet;

  // Recursive arguments
  std::string::const_iterator begin;
  std::string::const_iterator it;
  std::string::const_iterator end;
  bool ignoreNext = false;
  AnnotatedString result;
  std::vector<AnimatedTextStyle> styleStack;
};

}  // namespace loki::gfx
