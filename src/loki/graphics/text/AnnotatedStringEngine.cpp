#include "AnnotatedStringEngine.hpp"

namespace loki::gfx {

AnnotatedStringEngine::AnnotatedStringEngine(const Stylesheet& _stylesheet)
    : stylesheet(_stylesheet) {}

AnnotatedString AnnotatedStringEngine::parseAnnotatedString(
    const std::string& annotatedString) {
  begin = annotatedString.begin();
  it = annotatedString.begin();
  end = annotatedString.end();
  ignoreNext = false;
  result.clear();
  styleStack.clear();

  styleStack.push_back(stylesheet.getDefaultStyle());
  readText();

  return result;
}

void AnnotatedStringEngine::readText() {
  for (; it != end; ++it) {
    if (ignoreNext) {
      ignoreNext = false;
      continue;
    }
    switch (*it) {
      case '[':
        if (begin != it) {
          result.emplace_back(std::string{begin, it}, styleStack.back());
        }
        begin = it + 1;
        styleStack.push_back(styleStack.back());
        readStyle();
        break;

      case ']':
        if (styleStack.size() <= 1) {
          throw std::runtime_error("']' has no matching '['");
        }
        result.emplace_back(std::string{begin, it}, styleStack.back());
        begin = it + 1;
        styleStack.pop_back();
        break;

      case '\\':
        ignoreNext = true;
        break;

      default:
        break;
    }
  }
  if (styleStack.size() > 1) {
    throw std::runtime_error("'[' has no matching ']'");
  }
  if (begin != it) {
    result.emplace_back(std::string{begin, it}, styleStack.back());
    begin = it;
  }
}

void AnnotatedStringEngine::readStyle() {
  while (it != end) {
    switch (*it) {
      case '[':
        throw std::runtime_error("No '[' allowed in style list");
        break;

      case ']':
        // no textbutton (pauses, etc.)
        if (begin == it) {
          throw std::runtime_error("Empty style name not allowed");
        }
        styleStack.back().overrideWith(
            stylesheet.getStyle(std::string{begin, it}));
        begin = it + 1;
        result.emplace_back(std::string{}, styleStack.back());
        styleStack.pop_back();
        return;

      case ',':
        if (begin == it) {
          throw std::runtime_error("Empty style name not allowed");
        }
        styleStack.back().overrideWith(
            stylesheet.getStyle(std::string{begin, it}));
        begin = it + 1;
        break;

      case ':':
        if (begin == it) {
          throw std::runtime_error("Empty style name not allowed");
        }
        styleStack.back().overrideWith(
            stylesheet.getStyle(std::string{begin, it}));
        begin = it + 1;
        return;
    }
  }
}

}  // namespace loki::gfx
