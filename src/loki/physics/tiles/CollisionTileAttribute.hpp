#pragma once

#include <loki/physics/shapes/PhysicsShapeParams.hpp>
#include <loki/tiles/TileSetData.hpp>

namespace loki::physics {

struct CollisionTileAttribute : public tiles::TileAttribute {
  bool isSolid = false;
  std::unique_ptr<PhysicsShapeParams> shapeParams;
  LOKI_RTTI_CLASS_DECLARE(CollisionTileAttribute)
};

}  // namespace loki::physics

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::physics::CollisionTileAttribute, loki::tiles::TileAttribute)
LOKI_REFLECTION_CLASS_FIELD(isSolid)
LOKI_REFLECTION_CLASS_FIELD(shapeParams)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::physics::CollisionTileAttribute)