#include "InputTriggers.hpp"

#include "InputManager.hpp"
#include "loki/core/services/ServiceRegistry.hpp"

namespace loki::system {

InputTriggerStatus KeyTrigger::getStatus(InputMethod inputMethod) const {
  if (!(inputMethod & InputMethod::Keyboard))
    return {};

  return {sf::Keyboard::isKeyPressed(key)};
}

InputTriggerStatus MouseButtonTrigger::getStatus(InputMethod inputMethod) const {
  if (!(inputMethod & InputMethod::Mouse))
    return {};

  return {sf::Mouse::isButtonPressed(button)};
}

InputTriggerStatus JoystickAxisTrigger::getStatus(InputMethod inputMethod) const {
  if (!(inputMethod & InputMethod::Joystick))
    return {};

  float axisPos = sf::Joystick::getAxisPosition(getJoystickId(inputMethod), axis);
  float deadZone = getService<InputManager>().getDeadZone(axis);
  bool activeUp = direction != JoystickAxisDirection::NEGATIVE && axisPos > deadZone;
  bool activeDown = direction != JoystickAxisDirection::POSITIVE && axisPos < -deadZone;
  return {activeUp || activeDown, axisPos};
}

InputTriggerStatus JoystickButtonTrigger::getStatus(InputMethod inputMethod) const {
  if (!(inputMethod & InputMethod::Mouse))
    return {};

  return {sf::Joystick::isButtonPressed(getJoystickId(inputMethod), button)};
}

}  // namespace loki::system
