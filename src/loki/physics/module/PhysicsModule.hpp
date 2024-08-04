#pragma once

#include <loki/core/utils/Memory.hpp>
#include <loki/system/modules/GameModule.hpp>
#include <loki/physics/world/PhysicsWorld.hpp>

namespace loki::physics {

class PhysicsModule : public system::GameModule {
 public:
  void registerAsAService(core::ServiceRegistry& serviceRegistry) override;
  core::BorrowerPtr<PhysicsWorld> createWorld(PhysicsWorldParams&& params);

 private:
  std::vector<core::OwnerPtr<PhysicsWorld>> worlds;

  LOKI_RTTI_CLASS_DECLARE(PhysicsModule)
};

}  // namespace loki::physics

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::GameModule, loki::physics::PhysicsModule)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::physics::PhysicsModule)