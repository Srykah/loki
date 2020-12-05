/*!
 * \file Widget.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

namespace loki::gui {

class Widget {
 public:
  virtual ~Widget() = default;

  virtual void hide();
  virtual void unhide();
  virtual void setHidden(bool _hidden) final;
  [[nodiscard]] bool isHidden() const;

  virtual void enable();
  virtual void disable();
  virtual void setEnabled(bool _enabled) final;
  [[nodiscard]] bool isEnabled() const;

  virtual void focus();
  virtual void unfocus();
  virtual void setFocused(bool _focused) final;
  [[nodiscard]] bool isFocused() const;

  virtual void activate();
  virtual void deactivate();
  virtual void setActive(bool _active) final;
  [[nodiscard]] bool isActive() const;

 private:
  bool hidden = false;
  bool enabled = true;
  bool focused = false;
  bool active = false;
};

}  // namespace loki::gui