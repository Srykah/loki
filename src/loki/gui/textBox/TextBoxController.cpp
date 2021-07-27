/*!
 * \file TextBoxController.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "TextBoxController.hpp"
#include "AbstractTextBox.hpp"
#include <vector>

namespace loki::gui {

void TextBoxController::hide() {
  Widget::hide();
  view->hide();
}

void TextBoxController::unhide() {
  Widget::unhide();
  view->unhide();
}

void TextBoxController::enable() {
  Widget::enable();
  view->enable();
}

void TextBoxController::disable() {
  Widget::disable();
  view->disable();
}

void TextBoxController::focus() {
  Widget::focus();
  view->focus();
}

void TextBoxController::unfocus() {
  Widget::unfocus();
  view->unfocus();
}

void TextBoxController::activate() {
  Widget::activate();
  view->activate();
}

void TextBoxController::deactivate() {
  Widget::deactivate();
  view->deactivate();
}

void TextBoxController::setView(AbstractTextBox* _view) {
  view = _view;
  view->setHidden(isHidden());
  view->setEnabled(isEnabled());
  view->setFocused(isFocused());
  view->setActive(isActive());
}

bool TextBoxController::hasEnded() const {
  return it == str.end() && view->hasEnded();
}

void TextBoxController::setString(const sf::String& _str) {
  str = _str;
  if (str.isEmpty()) {
    it = str.end();
    view->clear();
  } else {
    it = str.begin();
    advance();
  }
}

void TextBoxController::advance() {
  std::vector<sf::String> lines(1);
  bool separator = false;
  bool space = false;
  while (true) {
    if (it == str.end()) {
      // reached end of input, we stop
      break;
    } else if (*it == '\n' && it + 1 != str.end() && *(it + 1) == '\n') {
      // double newline : we count past those characters, then stop
      it += 2;
      break;
    } else if (*it == '\n') {
      // newline : count past the character, then...
      ++it;
      if (lines.back().isEmpty()) {
        // we're already on a new line, so we do nothing
        continue;
      } else if (lines.size() < view->getLineCount()) {
        // we have room, so we make a new line
        lines.emplace_back("");
      } else {
        // we don't have room, so we stop
        break;
      }
    } else if (*it == ' ') {
      // space : we count past, then...
      ++it;
      if (lines.back().isEmpty()) {
        // we're on the beginning of a line, so we ignore
        continue;
      } else {
        // we remember to add a space before the next word
        space = true;
      }
    } else if (*it == '|') {
      // wordwrap character : we count past and remember to add a separator if
      // needed
      ++it;
      separator = true;
    } else {
      // get next word (part)
      static const sf::String wordSeparators("| \n");
      auto wordEndIt =
          std::find_first_of(it, std::as_const(str).end(),
                             wordSeparators.begin(), wordSeparators.end());
      // *wordEndIt is now a wordSeparator or the end of str
      sf::String nextWord =
          std::basic_string<sf::Uint32>(it, wordEndIt);  // *wordEndIt excluded

      // see if it fits in the current line
      sf::String testLine = lines.back() + nextWord;
      if (it != str.end() && *it == '|') {
        testLine += '-';
      }
      if (view->canFitInLine(testLine, lines.size() - 1)) {
        it = wordEndIt;  // here *it becomes the separator / end of str so it
                         // can be analysed later
        if (space) {
          lines.back() += ' ';
          space = false;
        }
        lines.back() += nextWord;
      } else {
        if (separator) {
          lines.back() += '-';
          separator = false;
        }
        if (lines.size() == view->getLineCount()) {
          break;
          // note : we do not change it so the current word will be kept for
          // later
        } else {
          lines.emplace_back(nextWord);
        }
      }
    }
  }
  view->setLines(std::move(lines));
}

}  // namespace loki::gui
