#include "EditorModule.hpp"

namespace loki::editor {

void EditorModule::registerAsAService(core::ServiceRegistry& serviceRegistry) {
  serviceRegistry.registerService(*this);
}

void EditorModule::init() {}

}  // namespace loki::editor
