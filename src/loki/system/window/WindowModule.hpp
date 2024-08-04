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
  void update(sf::Time delta) override;

  void draw(const sf::Drawable& drawable);

 private:
  std::string windowTitle;
  sf::Vector2u windowSize;
  WindowStyle windowStyle = WindowStyle::DEFAULT;
  sf::Vector2u minimumSize;
  sf::Vector2u internalResolution;

  Window window;
  std::vector<sf::Event> events;

  LOKI_RTTI_CLASS_DECLARE(WindowModule)
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