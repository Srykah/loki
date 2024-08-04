#pragma once

#include <filesystem>

#include <SFML/Window.hpp>

#include <loki/core/reflection/sfmlTypesInfo.hpp>
#include <loki/core/rtti/BaseObject.hpp>
#include <loki/system/input/InputConfig.hpp>
#include <loki/system/input/InputState.hpp>
#include <loki/system/input/PlayerConfig.hpp>
#include <loki/system/modules/GameModule.hpp>

namespace loki::system {

class InputModule final : public GameModule {
 public:
  InputModule();
  void registerAsAService(core::ServiceRegistry& serviceRegistry) override;

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

  LOKI_RTTI_CLASS_DECLARE(InputModule)
};

}  // namespace loki::system

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::GameModule, loki::system::InputModule)
LOKI_REFLECTION_CLASS_FIELD(inputConfigs)
LOKI_REFLECTION_CLASS_FIELD(deadZones)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::system::InputModule)