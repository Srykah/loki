#pragma once

#include <vector>

#include <SFML/System/Time.hpp>

#include <loki/core/reflection/basicTypesInfo.hpp>
#include <loki/system/ecs/Component.hpp>
#include <loki/system/scheduler/UpdateTraits.hpp>
#include <loki/physics/bodies/PhysicsBody.hpp>
#include <loki/physics/bodies/PhysicsBodyParams.hpp>
#include <loki/physics/shapes/PhysicsShapeParams.hpp>

namespace loki::physics {

class PhysicsBodyComponent : public system::Component {
 public:
  void onBeginInit() override;
  void onEndInit() override;
  void onPrePhysics(sf::Time dt) override;
  void onPhysicsResult(sf::Time dt) override;

  PhysicsBody& getBody() { return body; }

  [[nodiscard]] sf::FloatRect getBoundingBox() const;

 private:
  PhysicsBodyParams bodyParams;
  std::vector<std::unique_ptr<PhysicsShapeParams>> shapeParams;
  PhysicsBody body;

  LOKI_RTTI_CLASS_DECLARE(PhysicsBodyComponent)
};

}  // namespace loki::physics

LOKI_REFLECTION_COMPONENT_BEGIN(loki::physics::PhysicsBodyComponent)
LOKI_REFLECTION_CLASS_FIELD(bodyParams)
LOKI_REFLECTION_CLASS_FIELD(shapeParams)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::physics::PhysicsBodyComponent)
