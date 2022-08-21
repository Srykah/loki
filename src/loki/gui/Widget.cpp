#include "Widget.hpp"

namespace loki::gui {

void Widget::onUpdate(Widget::Callback&& callback) {
  onUpdateCb = std::move(callback);
}

void Widget::hide() {
  hidden = true;
  hideImpl();
  if (onHideCb) {
    onHideCb(*this);
  }
}

void Widget::unhide() {
  hidden = false;
  unhideImpl();
  if (onUnhideCb) {
    onUnhideCb(*this);
  }
}

void Widget::setHidden(bool _hidden) {
  if (_hidden != hidden) {
    if (_hidden) {
      hide();
    } else {
      unhide();
    }
  }
}

bool Widget::isHidden() const {
  return hidden;
}

void Widget::onHide(Widget::Callback&& callback) {
  onHideCb = std::move(callback);
}

void Widget::onUnhide(Widget::Callback&& callback) {
  onUnhideCb = std::move(callback);
}

void Widget::enable() {
  enabled = true;
  enableImpl();
  if (onEnableCb) {
    onEnableCb(*this);
  }
}

void Widget::disable() {
  enabled = false;
  disableImpl();
  if (onDisableCb) {
    onDisableCb(*this);
  }
}

void Widget::setEnabled(bool _enabled) {
  if (_enabled != enabled) {
    if (_enabled) {
      enable();
    } else {
      disable();
    }
  }
}

bool Widget::isEnabled() const {
  return enabled;
}

void Widget::onEnable(Widget::Callback&& callback) {
  onEnableCb = std::move(callback);
}

void Widget::onDisable(Widget::Callback&& callback) {
  onDisableCb = std::move(callback);
}

void Widget::focus() {
  focused = true;
  focusImpl();
  if (onFocusCb) {
    onFocusCb(*this);
  }
}

void Widget::unfocus() {
  focused = false;
  unfocusImpl();
  if (onUnfocusCb) {
    onUnfocusCb(*this);
  }
}

void Widget::setFocused(bool _focused) {
  if (_focused != focused) {
    if (_focused) {
      focus();
    } else {
      unfocus();
    }
  }
}

bool Widget::isFocused() const {
  return focused;
}

void Widget::onFocus(Widget::Callback&& callback) {
  onFocusCb = std::move(callback);
}

void Widget::onUnfocus(Widget::Callback&& callback) {
  onUnfocusCb = std::move(callback);
}

void Widget::activate() {
  active = true;
  activateImpl();
  if (onActivateCb) {
    onActivateCb(*this);
  }
}

void Widget::deactivate() {
  active = false;
  deactivateImpl();
  if (onDeactivateCb) {
    onDeactivateCb(*this);
  }
}

void Widget::setActive(bool _active) {
  if (_active != active) {
    if (_active) {
      activate();
    } else {
      deactivate();
    }
  }
}

bool Widget::isActive() const {
  return active;
}

void Widget::onActivate(Widget::Callback&& callback) {
  onActivateCb = std::move(callback);
}

void Widget::onDeactivate(Widget::Callback&& callback) {
  onDeactivateCb = std::move(callback);
}

}  // namespace loki::gui
