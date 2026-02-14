#include "registerTypes.hpp"

#include <loki/tiles/TileMapDataComponent.hpp>

namespace loki::tiles {

void registerTypes(core::RuntimeObjectRegistry& runtimeObjectRegistry, system::ComponentRegistry& componentRegistry) {
  // components
#define LOKI_REGISTER_COMP(Comp)               \
  runtimeObjectRegistry.registerClass<Comp>(); \
  componentRegistry.registerComponent<Comp>()

  LOKI_REGISTER_COMP(TileMapDataComponent);

#undef LOKI_REGISTER_COMP
}

}  // namespace loki::tiles
