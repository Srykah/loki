#pragma once

#include <filesystem>

#include <SFML/Window.hpp>

#include <loki/core/reflection/sfmlTypesInfo.hpp>
#include <loki/core/runtimeObject/BaseObject.hpp>
#include <loki/system/input/InputConfig.hpp>
#include <loki/system/input/InputState.hpp>
#include <loki/system/input/PlayerConfig.hpp>
#include <loki/system/modules/GameModule.hpp>

namespace loki::system {

class InputManager final : public GameModule {
 public:
  InputManager();
  void registerAsAService(ServiceRegistry& serviceRegistry) override;

  void setPlayerConfig(PlayerConfig&& playerConfig, PlayerId playerId = 0);

  void update(sf::Time dt) override;

  [[nodiscard]] InputState getInputState(const InputId& inputId, PlayerId playerId = 0) const;

  [[nodiscard]] float getDeadZone(sf::Joystick::Axis axis) const;

 private:
  std::map<InputConfigId, InputConfig> inputConfigs;
  std::map<PlayerId, PlayerConfig> playerConfigs;
  std::map<sf::Joystick::Axis, float> deadZones;

  std::map<PlayerId, std::map<InputId, InputState>> inputStates;

  // fixme
  bool needsInit = true;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(InputManager)
};

}  // namespace loki::system

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::GameModule, loki::system::InputManager)
LOKI_REFLECTION_CLASS_FIELD(loki::system::InputManager, inputConfigs)
LOKI_REFLECTION_CLASS_FIELD(loki::system::InputManager, deadZones)
LOKI_REFLECTION_CLASS_END_RTTI(loki::system::InputManager)