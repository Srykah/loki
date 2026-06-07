#pragma once

#include <loki/core/rtti/RuntimeObjectRegistry.hpp>
#include <loki/system/ecs/ComponentRegistry.hpp>

namespace loki::physics {
void registerTypes(core::TypeRegistry& runtimeObjectRegistry, system::ComponentRegistry& componentRegistry);
}  // namespace loki::physics
