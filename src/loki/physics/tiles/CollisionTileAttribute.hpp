#pragma once

#include <loki/physics/shapes/PhysicsFixtureParams.hpp>
#include <loki/tiles/TileSetData.hpp>

namespace loki::physics {

struct CollisionTileAttribute : public tiles::TileAttribute {
  bool isSolid = false;
  PhysicsFixtureParams fixtureParams;
  LOKI_REFLECTION_CLASS_DECLARE_RTTI(CollisionTileAttribute)
};

}  // namespace loki::physics

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::tiles::TileAttribute, loki::physics::CollisionTileAttribute)
LOKI_REFLECTION_CLASS_FIELD(loki::physics::CollisionTileAttribute, isSolid)
LOKI_REFLECTION_CLASS_FIELD(loki::physics::CollisionTileAttribute, fixtureParams)
LOKI_REFLECTION_CLASS_END_RTTI(loki::physics::CollisionTileAttribute)