#include "registerTypes.hpp"

#include <loki/editor/modules/DebugDrawModule.hpp>
#include <loki/editor/modules/EditorModule.hpp>
#include <loki/editor/modules/ImGuiModule.hpp>

namespace loki::editor {

void registerTypes(core::RuntimeObjectRegistry& runtimeObjectRegistry, system::ComponentRegistry& componentRegistry) {
  // modules
  runtimeObjectRegistry.registerClass<DebugDrawModule>();
  runtimeObjectRegistry.registerClass<EditorModule>();
  runtimeObjectRegistry.registerClass<ImGuiModule>();
}

}  // namespace loki::app
