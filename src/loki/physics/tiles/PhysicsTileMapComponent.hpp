#pragma once

#include <loki/system/ecs/Component.hpp>
#include <loki/system/render/Drawable.hpp>
#include <loki/physics/bodies/PhysicsBody.hpp>
#include <loki/physics/bodies/PhysicsBodyParams.hpp>
#include <loki/tiles/TileMapDataComponent.hpp>

namespace loki::physics {

class PhysicsTileMapComponent : public system::Component, public system::DebugDrawable {
 public:
  void onStartInit() override;
  void onFinalizeInit() override;

  system::DrawOrder getDebugDrawOrder() const override;
  void debugDraw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  void createShapes(const tiles::TileMapData& data);

 private:
  PhysicsBodyParams bodyParams;
  PhysicsBody body;

  LOKI_REFLECTION_CLASS_DECLARE_RTTI(PhysicsTileMapComponent)
};

}  // namespace loki::physics

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::Component, loki::physics::PhysicsTileMapComponent)
LOKI_REFLECTION_CLASS_FIELD(loki::physics::PhysicsTileMapComponent, bodyParams)
LOKI_REFLECTION_CLASS_END_RTTI(loki::physics::PhysicsTileMapComponent)