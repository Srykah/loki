#include "registerTypes.hpp"

#include <loki/tiles/TileMapDataComponent.hpp>
#include <loki/tiles/TileSetData.hpp>

namespace loki::tiles {

void registerTypes(core::TypeRegistry& runtimeObjectRegistry, system::ComponentRegistry& componentRegistry) {
  // runtime types
  runtimeObjectRegistry.registerClass<TileAttribute>();
  runtimeObjectRegistry.registerClass<TileSetAttribute>();
  runtimeObjectRegistry.registerClass<SizeTileSetAttribute>();

  // components
#define LOKI_REGISTER_COMP(Comp)               \
  runtimeObjectRegistry.registerClass<Comp>(); \
  componentRegistry.registerComponent<Comp>()

  LOKI_REGISTER_COMP(TileMapDataComponent);

#undef LOKI_REGISTER_COMP
}

}  // namespace loki::tiles
