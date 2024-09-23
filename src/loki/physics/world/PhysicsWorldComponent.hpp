#pragma once

#include <loki/system/ecs/Component.hpp>
#include <loki/system/scheduler/UpdateTraits.hpp>
#include <loki/physics/world/PhysicsWorld.hpp>

namespace loki::physics {

class PhysicsWorldComponent : public system::Component {
 public:
  void onStartInit() override;
  void onPhysicsSimulation(sf::Time delta);

  PhysicsWorld* getWorld() const;

 private:
  PhysicsWorldParams worldParams;
  std::unique_ptr<PhysicsWorld> world;

  LOKI_RTTI_CLASS_DECLARE(PhysicsWorldComponent)
};

}  // namespace loki::physics

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::Component, loki::physics::PhysicsWorldComponent)
LOKI_REFLECTION_CLASS_FIELD(worldParams)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::physics::PhysicsWorldComponent)

LOKI_UPDATE_TRAITS_BEGIN(loki::physics::PhysicsWorldComponent)
LOKI_UPDATE_TRAITS_METHOD(PhysicsSimulation, onPhysicsSimulation)
LOKI_UPDATE_TRAITS_END()