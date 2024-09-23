#pragma once

#include <loki/system/ecs/Component.hpp>
#include <loki/physics/bodies/PhysicsBody.hpp>
#include <loki/physics/bodies/PhysicsBodyParams.hpp>
#include <loki/tiles/TileMapDataComponent.hpp>

namespace loki::physics {

class PhysicsTileMapComponent : public system::Component {
 public:
  void onStartInit() override;
  void onFinalizeInit() override;

 private:
  void createShapes(const tiles::TileMapData& data);

 private:
  PhysicsBodyParams bodyParams;
  PhysicsBody body;

  LOKI_RTTI_CLASS_DECLARE(PhysicsTileMapComponent)
};

}  // namespace loki::physics

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::Component, loki::physics::PhysicsTileMapComponent)
LOKI_REFLECTION_CLASS_FIELD(bodyParams)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::physics::PhysicsTileMapComponent)