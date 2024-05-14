#include "registerLokiTypes.hpp"

#include <loki/core/runtimeObject/RuntimeObjectRegistry.hpp>
#include <loki/core/services/ServiceRegistry.hpp>
#include <loki/system/ecs/ComponentRegistry.hpp>
#include <loki/graphics/sprites/SpriteComponent.hpp>
#include <loki/graphics/tiles/TileMapComponent.hpp>
#include <loki/physics/bodies/PhysicsBodyComponent.hpp>
#include <loki/physics/module/PhysicsModule.hpp>
#include <loki/physics/world/PhysicsWorldComponent.hpp>

namespace loki::app {

void registerLokiRuntimeTypes(core::RuntimeObjectRegistry& runtimeObjectRegistry) {
  // physics
  runtimeObjectRegistry.registerClass<physics::PhysicsShapeParams>();
  runtimeObjectRegistry.registerClass<physics::CircleShapeParams>();
  runtimeObjectRegistry.registerClass<physics::EdgeShapeParams>();
  runtimeObjectRegistry.registerClass<physics::PolygonShapeParams>();
  runtimeObjectRegistry.registerClass<physics::ChainShapeParams>();
}

void registerLokiModules(core::RuntimeObjectRegistry& runtimeObjectRegistry) {
  // physics
  runtimeObjectRegistry.registerClass<physics::PhysicsModule>();
}

void registerLokiComponents(core::RuntimeObjectRegistry& runtimeObjectRegistry,
                            system::ComponentRegistry& componentRegistry) {
#define LOKI_REGISTER_COMP(Comp)               \
  runtimeObjectRegistry.registerClass<Comp>(); \
  componentRegistry.registerComponent<Comp>()

  // graphics
  LOKI_REGISTER_COMP(graphics::SpriteComponent);
  LOKI_REGISTER_COMP(graphics::TileMapComponent);

  // physics
  LOKI_REGISTER_COMP(physics::PhysicsBodyComponent);
  LOKI_REGISTER_COMP(physics::PhysicsWorldComponent);

#undef LOKI_REGISTER_COMP
}

}  // namespace loki::app
