#include "EditorModule.hpp"

namespace loki::editor {

void EditorModule::registerAsAService(core::ServiceRegistry& serviceRegistry) {
  serviceRegistry.registerService(*this);
}

void EditorModule::init() {}

void EditorModule::update(system::UpdateStep updateStep, sf::Time dt) {}

}  // namespace loki::editor
