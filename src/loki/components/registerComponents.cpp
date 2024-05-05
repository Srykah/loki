#include "registerComponents.hpp"

#include <loki/core/runtimeObject/RuntimeObjectRegistry.hpp>
#include <loki/core/services/ServiceRegistry.hpp>
#include <loki/system/ecs/ComponentRegistry.hpp>
#include <loki/components/graphics/CircleShapeComponent.hpp>
#include <loki/components/graphics/SpriteComponent.hpp>

namespace loki::components {

void registerLokiComponents() {
  auto& compReg = getService<system::ComponentRegistry>();
  auto& runtimeObjectReg = getService<core::RuntimeObjectRegistry>();

#define LOKI_REGISTER_COMP(Comp)          \
  runtimeObjectReg.registerClass<Comp>(); \
  compReg.registerComponent<Comp>()

  LOKI_REGISTER_COMP(CircleShapeComponent);
  LOKI_REGISTER_COMP(SpriteComponent);

#undef LOKI_REGISTER_COMP
}

}  // namespace loki::components
