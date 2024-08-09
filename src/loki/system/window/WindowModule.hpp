#pragma once

#include <loki/core/reflection/basicTypesInfo.hpp>
#include <loki/core/reflection/sfmlTypesInfo.hpp>
#include <loki/system/modules/GameModule.hpp>

#include "Window.hpp"

namespace loki::system {

class WindowModule final : public GameModule {
 public:
  void registerAsAService(core::ServiceRegistry& serviceRegistry) override;
  void init() override;
  void update(sf::Time delta, UpdateSteps::InputPolling);
  void update(sf::Time delta, UpdateSteps::PreRender);
  void update(sf::Time delta, UpdateSteps::PostRender);
  static_assert(HasUpdateStep<WindowModule, UpdateStep::InputPolling>);
  static_assert(HasUpdateStep<WindowModule, UpdateStep::PreRender>);
  static_assert(HasUpdateStep<WindowModule, UpdateStep::PostRender>);

  Window& getWindow() { return window; }
  std::span<const sf::Event> getEvents() const { return events; }

 private:
  std::string windowTitle;
  sf::Vector2f windowSize;
  WindowStyle windowStyle = WindowStyle::DEFAULT;
  sf::Vector2f minimumSize;
  sf::Vector2f internalResolution;

  Window window;
  std::vector<sf::Event> events;

  LOKI_RTTI_CLASS_DECLARE(WindowModule)
  LOKI_GAMEMODULE_GET_UPDATE_TRAITS(WindowModule)
};

}  // namespace loki::system

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::GameModule, loki::system::WindowModule)
LOKI_REFLECTION_CLASS_FIELD(windowTitle)
LOKI_REFLECTION_CLASS_FIELD(windowSize)
LOKI_REFLECTION_CLASS_FIELD(windowStyle)
LOKI_REFLECTION_CLASS_FIELD(minimumSize)
LOKI_REFLECTION_CLASS_FIELD(internalResolution)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::system::WindowModule)