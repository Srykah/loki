/**
 * \file EventHandler.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <SFML/Window.hpp>
#include <loki/system/input/InputState.hpp>
#include <loki/system/input/PlayerConfig.hpp>
#include "loki/system/input/InputSettings.hpp"

namespace loki::input {

class EventHandler {
 public:
  EventHandler() = default;

  bool setSettings(InputSettings _settings);
  void setPlayerConfig(PlayerConfig&& playerConfig, int playerId = 0);

  void update(const sf::Time& delta);
  [[nodiscard]] InputState getInputState(const std::string& inputName,
                                         int playerId = 0) const;

 private:
  using PlayerInputStates = std::map<std::string, InputState>;

 private:
  InputSettings settings;
  std::vector<PlayerInputStates> playerInputStates;
  std::vector<PlayerConfig> playerConfigs;

 private:
  void resetStates(int playerId);
  void resetTransitions();
  static bool isActive(const InputTrigger& trigger, int joystickId);
  static void updateState(InputState& inputState, bool active);
};

}  // namespace loki::input
