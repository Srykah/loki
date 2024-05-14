#pragma once

#include <vector>

#include <loki/core/reflection/basicTypesInfo.hpp>
#include <loki/system/ecs/Component.hpp>
#include <loki/physics/bodies/PhysicsBody.hpp>
#include <loki/physics/bodies/PhysicsBodyParams.hpp>
#include <loki/physics/shapes/PhysicsFixtureParams.hpp>

namespace loki::physics {

class PhysicsBodyComponent : public system::Component {
 public:
  void onStartInit() override;
  void update(sf::Time dt) override;

 private:
  PhysicsBodyParams bodyParams;
  PhysicsBody body;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(PhysicsBodyComponent)
};

}  // namespace loki::physics

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::Component, loki::physics::PhysicsBodyComponent)
LOKI_REFLECTION_CLASS_FIELD(loki::physics::PhysicsBodyComponent, bodyParams)
LOKI_REFLECTION_CLASS_END_RTTI(loki::physics::PhysicsBodyComponent)