#pragma once

#include <loki/system/ecs/Component.hpp>
#include <loki/physics/world/PhysicsWorld.hpp>

namespace loki::physics {

class PhysicsWorldComponent : public system::Component {
 public:
  void onStartInit() override;
  void update(sf::Time dt) override;

  PhysicsWorld* getWorld() const;

 private:
  PhysicsWorldParams worldParams;
  core::BorrowerPtr<PhysicsWorld> world;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(PhysicsWorldComponent)
};

}  // namespace loki::physics

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::Component, loki::physics::PhysicsWorldComponent)
LOKI_REFLECTION_CLASS_FIELD(loki::physics::PhysicsWorldComponent, worldParams)
LOKI_REFLECTION_CLASS_END_RTTI(loki::physics::PhysicsWorldComponent)