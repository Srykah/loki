#include "registerTypes.hpp"

#include <loki/graphics/sprites/SpriteComponent.hpp>
#include <loki/graphics/tiles/GraphicsTileMapComponent.hpp>
#include <loki/graphics/tiles/TextureTileSetAttribute.hpp>

namespace loki::graphics {

void registerTypes(core::RuntimeObjectRegistry& runtimeObjectRegistry, system::ComponentRegistry& componentRegistry) {
  // runtime types
  runtimeObjectRegistry.registerClass<TextureTileSetAttribute>();

  // components
#define LOKI_REGISTER_COMP(Comp)               \
  runtimeObjectRegistry.registerClass<Comp>(); \
  componentRegistry.registerComponent<Comp>()

  LOKI_REGISTER_COMP(SpriteComponent);
  LOKI_REGISTER_COMP(GraphicsTileMapComponent);

#undef LOKI_REGISTER_COMP
}

}  // namespace loki::graphics
