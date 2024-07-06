#include "InputManager.hpp"

#include <fstream>

#include "loki/core/services/ServiceRegistry.hpp"

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

void InputManager::registerAsAService(ServiceRegistry& serviceRegistry) {
  serviceRegistry.registerService(*this);
}

void InputManager::setPlayerConfig(PlayerConfig&& playerConfig, PlayerId playerId) {
  playerConfigs[playerId] = std::move(playerConfig);
  inputStates[playerId] = {};
}

void InputManager::update(sf::Time delta) {
  if (needsInit) {
    setPlayerConfig(PlayerConfig{inputConfigs.begin()->first});
    needsInit = false;
  }

  for (const auto& [playerId, playerConfig] : playerConfigs) {
    const auto& inputConfig = inputConfigs.at(playerConfig.configId);
    for (const auto& [inputName, inputTriggers] : inputConfig) {
      InputTriggerStatus triggerStatus;
      for (const auto& trigger : inputTriggers) {
        triggerStatus = trigger->getStatus(playerConfig.inputMethod);
        if (triggerStatus.isActive)
          break;
      }
      inputStates.at(playerId)[inputName].update(triggerStatus);
    }
  }
}

InputState InputManager::getInputState(const InputId& inputId, PlayerId playerId) const {
  return inputStates.at(playerId).at(inputId);
}

float InputManager::getDeadZone(sf::Joystick::Axis axis) const {
  return deadZones.at(axis);
}

}  // namespace loki::system
