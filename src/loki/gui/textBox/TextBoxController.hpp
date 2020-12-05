/*!
 * \file TextBoxController.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/System/String.hpp>
#include <loki/gui/base/Widget.hpp>

namespace loki::gui {

class AbstractTextBox;

class TextBoxController : public Widget {
 public:
  TextBoxController() = default;
  ~TextBoxController() override = default;

  void hide() override;
  void unhide() override;
  void enable() override;
  void disable() override;
  void focus() override;
  void unfocus() override;
  void activate() override;
  void deactivate() override;

  void setView(AbstractTextBox* view);
  void setString(const sf::String& str);

  void handleInputs();

  [[nodiscard]] bool hasEnded() const;

 private:
  AbstractTextBox* view = nullptr;
  sf::String str;
  sf::String::ConstIterator it;
  void advance();
};

}
