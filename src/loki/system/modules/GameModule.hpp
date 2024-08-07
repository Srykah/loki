#pragma once

#include <loki/core/reflection/classMacros.hpp>
#include <loki/core/rtti/BaseObject.hpp>
#include <loki/core/services/ServiceRegistry.hpp>
#include <loki/system/scheduler/UpdateTraits.hpp>

namespace loki::system {

class GameModule : public core::BaseObject {
 public:
  virtual const BaseUpdateTraits& getUpdateTraits() const = 0;
  virtual void registerAsAService(core::ServiceRegistry& serviceRegistry) = 0;
  virtual void init() {}

  LOKI_RTTI_CLASS_DECLARE(GameModule)
};

}  // namespace loki::system

LOKI_REFLECTION_CLASS_BEGIN_NO_FACTORY(loki::system::GameModule)
LOKI_REFLECTION_CLASS_PARENT(loki::system::GameModule, loki::core::BaseObject)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::system::GameModule)

#define LOKI_GAMEMODULE_GET_UPDATE_TRAITS(Class)                             \
  const ::loki::system::BaseUpdateTraits& getUpdateTraits() const override { \
    static ::loki::system::UpdateTraits<Class> updateTraits;                 \
    return updateTraits;                                                     \
  }
