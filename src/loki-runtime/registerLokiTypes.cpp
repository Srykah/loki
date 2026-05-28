#include "registerLokiTypes.hpp"

#include <loki/system/registerTypes.hpp>
#include <loki/graphics/registerTypes.hpp>
#include <loki/physics/registerTypes.hpp>
#include <loki/editor/registerTypes.hpp>
#include <loki/tiles/registerTypes.hpp>

namespace loki::app {

void registerLokiTypes(core::RuntimeObjectRegistry& runtimeObjectRegistry,
                       system::ComponentRegistry& componentRegistry) {
  system::registerTypes(runtimeObjectRegistry, componentRegistry);
  physics::registerTypes(runtimeObjectRegistry, componentRegistry);
  tiles::registerTypes(runtimeObjectRegistry, componentRegistry);
  graphics::registerTypes(runtimeObjectRegistry, componentRegistry);
  editor::registerTypes(runtimeObjectRegistry, componentRegistry);
}

}  // namespace loki::app
