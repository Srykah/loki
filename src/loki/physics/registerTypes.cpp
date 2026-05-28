#include "registerTypes.hpp"

#include <loki/physics/bodies/PhysicsBodyComponent.hpp>
#include <loki/physics/tiles/CollisionTileAttribute.hpp>
#include <loki/physics/tiles/PhysicsTileMapComponent.hpp>
#include <loki/physics/world/PhysicsWorldComponent.hpp>

namespace loki::physics {

void registerTypes(core::RuntimeObjectRegistry& runtimeObjectRegistry, system::ComponentRegistry& componentRegistry) {
  // runtime types
  runtimeObjectRegistry.registerClass<PhysicsShapeParams>();
  runtimeObjectRegistry.registerClass<CircleShapeParams>();
  runtimeObjectRegistry.registerClass<SegmentShapeParams>();
  runtimeObjectRegistry.registerClass<PolygonShapeParams>();
  runtimeObjectRegistry.registerClass<BoxShapeParams>();
  runtimeObjectRegistry.registerClass<ChainShapeParams>();
  runtimeObjectRegistry.registerClass<CollisionTileAttribute>();

  // components
#define LOKI_REGISTER_COMP(Comp)               \
  runtimeObjectRegistry.registerClass<Comp>(); \
  componentRegistry.registerComponent<Comp>()

  LOKI_REGISTER_COMP(PhysicsBodyComponent);
  LOKI_REGISTER_COMP(PhysicsWorldComponent);
  LOKI_REGISTER_COMP(PhysicsTileMapComponent);

#undef LOKI_REGISTER_COMP
}

}  // namespace loki::physics
