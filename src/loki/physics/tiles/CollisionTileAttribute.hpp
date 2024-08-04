#pragma once

#include <loki/physics/shapes/PhysicsFixtureParams.hpp>
#include <loki/tiles/TileSetData.hpp>

namespace loki::physics {

struct CollisionTileAttribute : public tiles::TileAttribute {
  bool isSolid = false;
  PhysicsFixtureParams fixtureParams;
  LOKI_RTTI_CLASS_DECLARE(CollisionTileAttribute)
};

}  // namespace loki::physics

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::tiles::TileAttribute, loki::physics::CollisionTileAttribute)
LOKI_REFLECTION_CLASS_FIELD(isSolid)
LOKI_REFLECTION_CLASS_FIELD(fixtureParams)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::physics::CollisionTileAttribute)