#include "registerTypes.hpp"

#include <loki/system/box/BoundingBoxComponent.hpp>
#include <loki/system/input/InputModule.hpp>
#include <loki/system/input/InputTriggers.hpp>
#include <loki/system/render/RendererModule.hpp>
#include <loki/system/window/WindowModule.hpp>

namespace loki::system {

void registerTypes(core::RuntimeObjectRegistry& runtimeObjectRegistry, system::ComponentRegistry& componentRegistry) {
  // runtime types
  runtimeObjectRegistry.registerClass<InputTrigger>();
  runtimeObjectRegistry.registerClass<KeyTrigger>();
  runtimeObjectRegistry.registerClass<MouseButtonTrigger>();
  runtimeObjectRegistry.registerClass<JoystickAxisTrigger>();
  runtimeObjectRegistry.registerClass<JoystickButtonTrigger>();

  // modules
  runtimeObjectRegistry.registerClass<WindowModule>();
  runtimeObjectRegistry.registerClass<InputModule>();
  runtimeObjectRegistry.registerClass<RendererModule>();

  // components
#define LOKI_REGISTER_COMP(Comp)               \
  runtimeObjectRegistry.registerClass<Comp>(); \
  componentRegistry.registerComponent<Comp>()

  LOKI_REGISTER_COMP(BoundingBoxComponent);

#undef LOKI_REGISTER_COMP
}

}  // namespace loki::system
