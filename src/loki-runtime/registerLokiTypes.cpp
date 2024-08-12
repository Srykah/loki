#include "registerLokiTypes.hpp"

#include <loki/core/rtti/RuntimeObjectRegistry.hpp>
#include <loki/core/services/ServiceRegistry.hpp>
#include <loki/system/ecs/ComponentRegistry.hpp>
#include <loki/system/input/InputModule.hpp>
#include <loki/system/input/InputTriggers.hpp>
#include <loki/system/render/RendererModule.hpp>
#include <loki/system/window/WindowModule.hpp>
#include <loki/graphics/sprites/SpriteComponent.hpp>
#include <loki/graphics/tiles/GraphicsTileMapComponent.hpp>
#include <loki/graphics/tiles/TextureTileSetAttribute.hpp>
#include <loki/physics/bodies/PhysicsBodyComponent.hpp>
#include <loki/physics/tiles/CollisionTileAttribute.hpp>
#include <loki/physics/tiles/PhysicsTileMapComponent.hpp>
#include <loki/physics/world/PhysicsWorldComponent.hpp>
#include <loki/editor/modules/EditorModule.hpp>
#include <loki/editor/modules/ImGuiModule.hpp>
#include <loki/tiles/TileMapDataComponent.hpp>

namespace loki::app {

void registerLokiRuntimeTypes(core::RuntimeObjectRegistry& runtimeObjectRegistry) {
  // system
  runtimeObjectRegistry.registerClass<system::InputTrigger>();
  runtimeObjectRegistry.registerClass<system::KeyTrigger>();
  runtimeObjectRegistry.registerClass<system::MouseButtonTrigger>();
  runtimeObjectRegistry.registerClass<system::JoystickAxisTrigger>();
  runtimeObjectRegistry.registerClass<system::JoystickButtonTrigger>();
  // tiles
  runtimeObjectRegistry.registerClass<tiles::TileAttribute>();
  runtimeObjectRegistry.registerClass<tiles::TileSetAttribute>();
  runtimeObjectRegistry.registerClass<tiles::SizeTileSetAttribute>();
  // graphics
  runtimeObjectRegistry.registerClass<graphics::TextureTileSetAttribute>();
  // physics
  runtimeObjectRegistry.registerClass<physics::PhysicsShapeParams>();
  runtimeObjectRegistry.registerClass<physics::CircleShapeParams>();
  runtimeObjectRegistry.registerClass<physics::EdgeShapeParams>();
  runtimeObjectRegistry.registerClass<physics::PolygonShapeParams>();
  runtimeObjectRegistry.registerClass<physics::ChainShapeParams>();
  runtimeObjectRegistry.registerClass<physics::CollisionTileAttribute>();
}

void registerLokiModules(core::RuntimeObjectRegistry& runtimeObjectRegistry) {
  // system
  runtimeObjectRegistry.registerClass<system::WindowModule>();
  runtimeObjectRegistry.registerClass<system::InputModule>();
  runtimeObjectRegistry.registerClass<system::RendererModule>();

  // editor
  runtimeObjectRegistry.registerClass<editor::EditorModule>();
  runtimeObjectRegistry.registerClass<editor::ImGuiModule>();
}

void registerLokiComponents(core::RuntimeObjectRegistry& runtimeObjectRegistry,
                            system::ComponentRegistry& componentRegistry) {
#define LOKI_REGISTER_COMP(Comp)               \
  runtimeObjectRegistry.registerClass<Comp>(); \
  componentRegistry.registerComponent<Comp>()

  // tiles
  LOKI_REGISTER_COMP(tiles::TileMapDataComponent);

  // graphics
  LOKI_REGISTER_COMP(graphics::SpriteComponent);
  LOKI_REGISTER_COMP(graphics::GraphicsTileMapComponent);

  // physics
  LOKI_REGISTER_COMP(physics::PhysicsBodyComponent);
  LOKI_REGISTER_COMP(physics::PhysicsWorldComponent);
  LOKI_REGISTER_COMP(physics::PhysicsTileMapComponent);

#undef LOKI_REGISTER_COMP
}

}  // namespace loki::app
