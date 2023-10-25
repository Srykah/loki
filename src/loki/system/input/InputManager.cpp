#include "InputManager.hpp"

#include <fstream>

namespace loki::system {

InputManager::InputManager()
    : deadZones({
          {sf::Joystick::Axis::X, 0.f},
          {sf::Joystick::Axis::Y, 0.f},
          {sf::Joystick::Axis::Z, 0.f},
          {sf::Joystick::Axis::R, 0.f},
          {sf::Joystick::Axis::U, 0.f},
          {sf::Joystick::Axis::V, 0.f},
          {sf::Joystick::Axis::PovX, 0.f},
          {sf::Joystick::Axis::PovY, 0.f},
      }) {}

void InputManager::loadConfigs(const std::filesystem::path& path) {
  std::ifstream fs(path);
  core::json json;
  fs >> json;
  json.at("configs").get_to(inputConfigs);
  json.at("deadZones").get_to(deadZones);
}

void InputManager::setPlayerConfig(PlayerConfig&& playerConfig, PlayerId playerId) {
  playerConfigs[playerId] = std::move(playerConfig);
  inputStates[playerId] = {};
}

void InputManager::update(const sf::Time& delta) {
  for (const auto& [playerId, playerConfig] : playerConfigs) {
    const auto& inputConfig = inputConfigs.at(playerConfig.configId);
    for (const auto& [inputName, inputTriggers] : inputConfig) {
      bool active = false;
      float value = 0.f;
      for (const auto& trigger : inputTriggers) {
        std::tie(active, value) = getTriggerStatus(trigger, playerConfig.inputMethod);
        if (active) {
          break;
        }
      }
      inputStates.at(playerId)[inputName].update(active, value);
    }
  }
}

InputState InputManager::getInputState(const InputId& inputId, PlayerId playerId) const {
  return inputStates.at(playerId).at(inputId);
}

std::pair<bool, float> InputManager::getTriggerStatus(const InputTrigger& trigger, InputMethod inputMethod) const {
  if (std::holds_alternative<MouseButtonTrigger>(trigger) && inputMethod & InputMethod::Mouse) {
    const auto& mouseButton = std::get<MouseButtonTrigger>(trigger);
    return {sf::Mouse::isButtonPressed(mouseButton), 1.f};
  } else if (std::holds_alternative<KeyTrigger>(trigger) && inputMethod & InputMethod::Keyboard) {
    const auto& key = std::get<KeyTrigger>(trigger);
    return {sf::Keyboard::isKeyPressed(key), 1.f};
  } else if (std::holds_alternative<JoystickButtonTrigger>(trigger) && inputMethod & InputMethod::Joystick) {
    const auto& joystickButton = std::get<JoystickButtonTrigger>(trigger);
    return {sf::Joystick::isButtonPressed(getJoystickId(inputMethod), joystickButton), 1.f};
  } else if (std::holds_alternative<JoystickAxisTrigger>(trigger) && inputMethod & InputMethod::Joystick) {
    const auto& axisTrigger = std::get<JoystickAxisTrigger>(trigger);
    auto axisPos = sf::Joystick::getAxisPosition(getJoystickId(inputMethod), axisTrigger.axis);
    bool activeUp =
        axisTrigger.direction != JoystickAxisTrigger::Direction::NEGATIVE && axisPos > deadZones.at(axisTrigger.axis);
    bool activeDown =
        axisTrigger.direction != JoystickAxisTrigger::Direction::POSITIVE && axisPos < -deadZones.at(axisTrigger.axis);
    return {activeUp || activeDown, axisPos};
  }

  return {false, 0.f};
}

}  // namespace loki::system
