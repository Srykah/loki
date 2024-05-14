#pragma once

#include <SFML/System/Time.hpp>

#include <loki/core/reflection/classMacros.hpp>
#include <loki/core/runtimeObject/BaseObject.hpp>

namespace loki::system {
class ServiceRegistry;

class GameModule : public core::BaseObject {
 public:
  virtual void registerAsAService(ServiceRegistry& serviceRegistry) = 0;
  virtual void update(sf::Time dt) {}

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(GameModule)
};

}  // namespace loki::system

LOKI_REFLECTION_CLASS_BEGIN_NO_FACTORY(loki::system::GameModule)
LOKI_REFLECTION_CLASS_PARENT(loki::system::GameModule, loki::core::BaseObject)
LOKI_REFLECTION_CLASS_END_RTTI(loki::system::GameModule)