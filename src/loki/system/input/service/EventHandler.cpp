/**
 * \file EventHandler.cpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "EventHandler.hpp"
#include <loki/core/utils/IterAdapters.hpp>

namespace loki::input {

bool EventHandler::setSettings(InputSettings _settings) {
  settings = std::move(_settings);
  return true;
}

void EventHandler::setPlayerConfig(PlayerConfig&& playerConfig, int playerId) {
  if (playerId < playerConfigs.size()) {
    playerConfigs.at(playerId) = playerConfig;
  } else if (playerId == playerConfigs.size()) {
    playerConfigs.emplace_back(playerConfig);
  } else {
    throw std::out_of_range("playerId too big");
  }
  resetStates(playerId);
}

void EventHandler::resetStates(int playerId) {
  PlayerInputStates* inputStates;
  if (playerId < playerInputStates.size()) {
    inputStates = &playerInputStates.at(playerId);
  } else if (playerId == playerInputStates.size()) {
    playerInputStates.emplace_back();
    inputStates = &playerInputStates.back();
  } else {
    throw std::out_of_range("playerId too big");
  }
  for (auto&& [inputName, _] :
       settings.configs.at(playerConfigs.at(playerId).config)) {
    inputStates->emplace(std::piecewise_construct,
                         std::forward_as_tuple(inputName),
                         std::forward_as_tuple());
  }
}

void EventHandler::update(const sf::Time& delta) {
  // reset transitions
  resetTransitions();

  for (auto&& [inputStates, currentConfig] :
       common::zip(playerInputStates, playerConfigs)) {
    const auto& configData = settings.configs.at(currentConfig.config);
    for (auto&& [inputName, inputState] : inputStates) {
      bool active = false;
      for (const auto& trigger : configData.at(inputName)) {
        active = active || isActive(trigger, currentConfig.joystickId);
      }
      updateState(inputState, active);
    }
  }
}

void EventHandler::resetTransitions() {
  for (auto& inputStates : playerInputStates) {
    for (auto&& [inputName, inputState] : inputStates) {
      if (inputState.status == InputState::TRIGGERED) {
        inputState.status = InputState::ACTIVE;
      } else if (inputState.status == InputState::ENDED) {
        inputState.status = InputState::INACTIVE;
      }
    }
  }
}

bool EventHandler::isActive(const InputTrigger& trigger, int joystickId) {
  if (std::holds_alternative<MouseButtonTrigger>(trigger)) {
    const auto& mouseButton = std::get<MouseButtonTrigger>(trigger);
    return sf::Mouse::isButtonPressed(mouseButton);
  } else if (std::holds_alternative<KeyTrigger>(trigger)) {
    const auto& key = std::get<KeyTrigger>(trigger);
    return sf::Keyboard::isKeyPressed(key);
  } else if (std::holds_alternative<JoystickButtonTrigger>(trigger)) {
    const auto& joystickButton = std::get<JoystickButtonTrigger>(trigger);
    return sf::Joystick::isButtonPressed(joystickId, joystickButton);
  } else if (std::holds_alternative<JoystickAxisTrigger>(trigger)) {
    const auto& axisTrigger = std::get<JoystickAxisTrigger>(trigger);
    if (axisTrigger.direction == JoystickAxisTrigger::Direction::POSITIVE) {
      return sf::Joystick::getAxisPosition(joystickId, axisTrigger.axis) >
             axisTrigger.deadZone;
    } else if (axisTrigger.direction ==
               JoystickAxisTrigger::Direction::NEGATIVE) {
      return sf::Joystick::getAxisPosition(joystickId, axisTrigger.axis) <
             -axisTrigger.deadZone;
    }
  }

  return false;
}

void EventHandler::updateState(InputState& inputState, bool active) {
  if (active && inputState.status == InputState::INACTIVE) {
    inputState.status = InputState::TRIGGERED;
  } else if (!active && inputState.status == InputState::ACTIVE) {
    inputState.status = InputState::ENDED;
  }
}

InputState EventHandler::getInputState(const std::string& inputName,
                                       int playerId) const {
  return playerInputStates.at(playerId).at(inputName);
}

}  // namespace loki::input
