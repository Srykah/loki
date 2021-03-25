/*!
 * \file EventTextBoxController.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <loki/input/service/EventHandler.hpp>
#include "TextBoxController.hpp"

namespace loki::gui {

class EventTextBoxController : public TextBoxController {
 public:
  EventTextBoxController(loki::input::EventHandler& eventHandler,
                         std::string inputName);

  void setInputName(std::string inputName);
  [[nodiscard]] const std::string& getInputName() const;

  void handleInputs();

 private:
  loki::input::EventHandler& eventHandler;
  std::string inputName;
};

}  // namespace loki::gui
