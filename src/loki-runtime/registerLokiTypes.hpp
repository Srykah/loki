#pragma once

#include <loki/core/rtti/RuntimeObjectRegistry.hpp>
#include <loki/system/ecs/ComponentRegistry.hpp>

namespace loki::app {
void registerLokiTypes(core::TypeRegistry& runtimeObjectRegistry, system::ComponentRegistry& componentRegistry);
}  // namespace loki::app
