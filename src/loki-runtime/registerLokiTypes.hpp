#pragma once

#include <loki/core/rtti/RuntimeObjectRegistry.hpp>
#include <loki/system/ecs/ComponentRegistry.hpp>

namespace loki::app {

void registerLokiRuntimeTypes(core::RuntimeObjectRegistry& runtimeObjectRegistry);
void registerLokiModules(core::RuntimeObjectRegistry& runtimeObjectRegistry);
void registerLokiComponents(core::RuntimeObjectRegistry& runtimeObjectRegistry,
                            system::ComponentRegistry& componentRegistry);

}  // namespace loki::app
