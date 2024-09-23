#pragma once

#include <vector>

#include <SFML/System/Time.hpp>

#include <loki/core/reflection/basicTypesInfo.hpp>
#include <loki/system/ecs/Component.hpp>
#include <loki/system/scheduler/UpdateTraits.hpp>
#include <loki/physics/bodies/PhysicsBody.hpp>
#include <loki/physics/bodies/PhysicsBodyParams.hpp>
#include <loki/physics/shapes/PhysicsFixtureParams.hpp>

namespace loki::physics {

class PhysicsBodyComponent : public system::Component {
 public:
  void onStartInit() override;
  void onFinalizeInit() override;
  void onPrePhysics(sf::Time dt);
  void onPhysicsResult(sf::Time dt);

  PhysicsBody& getBody() { return body; }

 private:
  PhysicsBodyParams bodyParams;
  std::vector<PhysicsFixtureParams> fixtureParams;
  PhysicsBody body;

  LOKI_RTTI_CLASS_DECLARE(PhysicsBodyComponent)
};

}  // namespace loki::physics

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::Component, loki::physics::PhysicsBodyComponent)
LOKI_REFLECTION_CLASS_FIELD(bodyParams)
LOKI_REFLECTION_CLASS_FIELD(fixtureParams)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::physics::PhysicsBodyComponent)

LOKI_UPDATE_TRAITS_BEGIN(loki::physics::PhysicsBodyComponent)
LOKI_UPDATE_TRAITS_METHOD(PrePhysics, onPrePhysics)
LOKI_UPDATE_TRAITS_METHOD(PhysicsResult, onPhysicsResult)
LOKI_UPDATE_TRAITS_END()
