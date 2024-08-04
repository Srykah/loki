#pragma once

#include <loki/core/rtti/BaseObject.hpp>
#include <loki/system/scheduler/UpdateStep.hpp>

namespace loki::system {

class ScheduledItem : public core::BaseObject {
 public:
  virtual void init(){};
  virtual void update(UpdateStep updateStep, sf::Time delta){};

  LOKI_RTTI_CLASS_DECLARE(ScheduledItem)
};

}  // namespace loki::system

LOKI_REFLECTION_CLASS_BEGIN_NO_FACTORY(loki::system::ScheduledItem)
LOKI_REFLECTION_CLASS_PARENT(loki::system::ScheduledItem, loki::core::BaseObject)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::system::ScheduledItem)
