#pragma once

#include <SFML/System/Time.hpp>

#include <loki/core/reflection/classMacros.hpp>
#include <loki/core/rtti/BaseObject.hpp>
#include <loki/core/services/ServiceRegistry.hpp>
#include <loki/system/scheduler/ScheduledItem.hpp>

namespace loki::system {

class GameModule : public ScheduledItem {
 public:
  virtual void registerAsAService(core::ServiceRegistry& serviceRegistry) = 0;
  virtual UpdateStep getUpdateStep() const { return UpdateStep::Default; }
  void update(UpdateStep updateStep, sf::Time dt) override {}

  LOKI_RTTI_CLASS_DECLARE(GameModule)
};

}  // namespace loki::system

LOKI_REFLECTION_CLASS_BEGIN_NO_FACTORY(loki::system::GameModule)
LOKI_REFLECTION_CLASS_PARENT(loki::system::GameModule, loki::system::ScheduledItem)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::system::GameModule)