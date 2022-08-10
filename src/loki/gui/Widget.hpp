/*!
 * \file Widget.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>
#include <functional>
#include <memory>

namespace loki::gui {

class Widget : public sf::Drawable, public sf::Transformable {
 public:
  using Callback = std::function<void(Widget&)>;
  using UPtr = std::unique_ptr<Widget>;

 public:
  virtual ~Widget() = default;

  virtual void update(sf::Time delta) {}
  void onUpdate(Callback&& callback);

  void hide();
  void unhide();
  void setHidden(bool _hidden);
  [[nodiscard]] bool isHidden() const;
  void onHide(Callback&& callback);
  void onUnhide(Callback&& callback);

  void enable();
  void disable();
  void setEnabled(bool _enabled);
  [[nodiscard]] bool isEnabled() const;
  void onEnable(Callback&& callback);
  void onDisable(Callback&& callback);

  void focus();
  void unfocus();
  void setFocused(bool _focused);
  [[nodiscard]] bool isFocused() const;
  void onFocus(Callback&& callback);
  void onUnfocus(Callback&& callback);

  void activate();
  void deactivate();
  void setActive(bool _active);
  [[nodiscard]] bool isActive() const;
  void onActivate(Callback&& callback);
  void onDeactivate(Callback&& callback);

 protected:
  virtual void hideImpl() {}
  virtual void unhideImpl() {}
  virtual void enableImpl() {}
  virtual void disableImpl() {}
  virtual void focusImpl() {}
  virtual void unfocusImpl() {}
  virtual void activateImpl() {}
  virtual void deactivateImpl() {}

 private:
  bool hidden = false;
  bool enabled = true;
  bool focused = false;
  bool active = false;
  Callback onHideCb;
  Callback onUnhideCb;
  Callback onEnableCb;
  Callback onDisableCb;
  Callback onFocusCb;
  Callback onUnfocusCb;
  Callback onActivateCb;
  Callback onDeactivateCb;
  Callback onUpdateCb;
};

}  // namespace loki::gui
