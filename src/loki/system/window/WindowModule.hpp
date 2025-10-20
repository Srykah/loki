#pragma once

#include <span>

#include <loki/core/reflection/basicTypesInfo.hpp>
#include <loki/core/reflection/sfmlTypesInfo.hpp>
#include <loki/system/modules/GameModule.hpp>

#include "Window.hpp"

namespace loki::system {

class WindowModule final : public GameModule {
 public:
  ~WindowModule() override = default;
  [[nodiscard]] const BaseUpdateTraits& getUpdateTraits() const override;
  void registerAsAService(core::ServiceRegistry& serviceRegistry) override;
  void init() override;
  void onInputPolling(sf::Time delta) override;
  void onPreRender(sf::Time delta) override;
  void onPostRender(sf::Time delta) override;

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
};

}  // namespace loki::system

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::WindowModule, loki::system::GameModule)
LOKI_REFLECTION_CLASS_FIELD(windowTitle)
LOKI_REFLECTION_CLASS_FIELD(windowSize)
LOKI_REFLECTION_CLASS_FIELD(windowStyle)
LOKI_REFLECTION_CLASS_FIELD(minimumSize)
LOKI_REFLECTION_CLASS_FIELD(internalResolution)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::system::WindowModule)
