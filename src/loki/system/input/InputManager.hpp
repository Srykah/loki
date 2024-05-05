#pragma once

#include <filesystem>

#include <SFML/Window.hpp>

#include <loki/core/runtimeObject/BaseObject.hpp>

#include "InputConfig.hpp"
#include "InputState.hpp"
#include "PlayerConfig.hpp"

namespace loki::system {

class InputManager : public core::BaseObject {
 public:
  InputManager();

  void loadConfigs(const std::filesystem::path& path);
  void setPlayerConfig(PlayerConfig&& playerConfig, PlayerId playerId = 0);

  void update(const sf::Time& delta);

  [[nodiscard]] InputState getInputState(const InputId& inputId, PlayerId playerId = 0) const;

 private:
  [[nodiscard]] std::pair<bool, float> getTriggerStatus(const InputTrigger& trigger, InputMethod inputMethod) const;

 private:
  std::map<InputConfigId, InputConfig> inputConfigs;
  std::map<PlayerId, PlayerConfig> playerConfigs;
  std::map<PlayerId, std::map<InputId, InputState>> inputStates;
  std::map<sf::Joystick::Axis, float> deadZones;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(InputManager)
};

}  // namespace loki::system

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::core::BaseObject, loki::system::InputManager)
LOKI_REFLECTION_CLASS_END_RTTI(loki::system::InputManager)