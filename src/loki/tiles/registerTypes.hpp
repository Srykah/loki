#pragma once

#include <loki/core/rtti/RuntimeObjectRegistry.hpp>
#include <loki/system/ecs/ComponentRegistry.hpp>

namespace loki::tiles {
void registerTypes(core::TypeRegistry& runtimeObjectRegistry, system::ComponentRegistry& componentRegistry);
}  // namespace loki::tiles
