/*!
 * \file EventTextBoxController.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "TextBox.hpp"
#include "TextBoxView.hpp"
#include <sstream>

namespace loki::gui {

TextBox::TextBox(const input::EventHandler& eventHandler,
                 std::string nextInputName)
    : eventHandler(eventHandler), nextInputName(std::move(nextInputName)) {}

void TextBox::setNextInputName(std::string _nextInputName) {
  nextInputName = std::move(_nextInputName);
}

const std::string& TextBox::getNextInputName() const {
  return nextInputName;
}

void TextBox::setAnnotatedString(const std::string& annotatedString) {
  splitString.clear();
  std::stringstream ss(annotatedString);
  do {
    splitString.emplace_back();
  } while (std::getline(ss, splitString.back(), '\f'));
  curString = 0;
  // view.setAnnotatedString(splitString[0]);
}

void TextBox::update(sf::Time delta) {
  if (eventHandler.getInputState(nextInputName).status ==
      loki::input::InputState::TRIGGERED) {
#if 0
    if (!view.hasAnimationStopped()) {
      view.skipAnimation();
    } else {
      if (view.hasEnded()) {
        ++curString;
        if (curString >= splitString.size()) {
          activate();
        } else {
          view.setAnnotatedString(splitString[curString]);
        }
      } else {
        view.advance();
      }
    }
#endif
  }
}

}  // namespace loki::gui
