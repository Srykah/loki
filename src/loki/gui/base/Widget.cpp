/*!
 * \file Widget.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "Widget.hpp"

namespace loki::gui {

void Widget::hide() {
  hidden = true;
}

void Widget::unhide() {
  hidden = false;
}

void Widget::setHidden(bool _hidden) {
  if (_hidden) {
    hide();
  } else {
    unhide();
  }
}

bool Widget::isHidden() const {
  return hidden;
}

void Widget::enable() {
  enabled = true;
}

void Widget::disable() {
  enabled = false;
}

void Widget::setEnabled(bool _enabled) {
  if (_enabled) {
    enable();
  } else {
    disable();
  }
}

bool Widget::isEnabled() const {
  return enabled;
}

void Widget::focus() {
  focused = true;
}

void Widget::unfocus() {
  focused = false;
}

void Widget::setFocused(bool _focused) {
  if (_focused) {
    focus();
  } else {
    unfocus();
  }
}

bool Widget::isFocused() const {
  return focused;
}

void Widget::activate() {
  active = true;
}

void Widget::deactivate() {
  active = false;
}

void Widget::setActive(bool _active) {
  if (_active) {
    activate();
  } else {
    deactivate();
  }
}

bool Widget::isActive() const {
  return active;
}

}  // namespace loki::gui