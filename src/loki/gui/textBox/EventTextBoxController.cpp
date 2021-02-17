/*!
 * \file EventTextBoxController.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "EventTextBoxController.hpp"

namespace loki::gui {

EventTextBoxController::EventTextBoxController(
    input::EventHandler& eventHandler,
    std::string inputName)
    : eventHandler(eventHandler), inputName(std::move(inputName)) {}

void EventTextBoxController::setInputName(std::string _inputName) {
  inputName = std::move(inputName);
}

const std::string& EventTextBoxController::getInputName() const {
  return inputName;
}

void EventTextBoxController::handleInputs() {
  if (!hasEnded() && eventHandler.getInputState(inputName).status ==
                         loki::input::InputState::TRIGGERED) {
    advance();
  }
}

}  // namespace loki::gui
