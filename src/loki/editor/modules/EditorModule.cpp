#include "EditorModule.hpp"

#include <imgui.h>

#include <loki/core/reflection/sfmlTypesInfo.hpp>
#include <loki/system/ecs/Component.hpp>
#include <loki/system/ecs/ComponentTraits.hpp>
#include <loki/system/scene/SceneManager.hpp>
#include <loki/editor/dynamicField/DynamicField.hpp>

namespace loki::editor {

void EditorModule::registerAsAService(core::ServiceRegistry& serviceRegistry) {
  serviceRegistry.registerService(*this);
}

void EditorModule::init() {
  sceneManager = &getService<system::SceneManager>();
}

void EditorModule::update(sf::Time dt, UpdateSteps::Render) {
  showScenePanel();
  showActorPanel();
}

void EditorModule::showScenePanel() {
  if (ImGui::Begin("Scene Panel")) {
    system::Actor actor = sceneManager->getCurrentScene()->getRoot();
    showActorHierarchy(actor);
  }
  ImGui::End();
}

void EditorModule::showActorPanel() {
  if (ImGui::Begin("Actor Panel") && selectedActor) {
    ImGui::TextUnformatted(selectedActor.getName().c_str());
    if (ImGui::CollapsingHeader("Transform")) {
      sf::Transformable transformable = selectedActor.getTransformable();
      if (DynamicField("Transform", transformable))
        selectedActor.setTransformable(std::move(transformable));
    }
    selectedActor.visitComponents([](const system::BaseComponentTraits& compTraits, void* compPtr) {
      system::Component& comp = compTraits.getAsComponent(compPtr);
      const auto& typeInfo = comp.getClassTypeInfo();
      const auto& classInfo = std::get<loki::core::ClassInfo>(typeInfo.info);
      if (ImGui::CollapsingHeader(classInfo.id.c_str())) {
        DynamicField(classInfo.id.c_str(), compPtr, typeInfo);
      }
    });
  }
  ImGui::End();
}

void EditorModule::showActorHierarchy(system::Actor actor) {
  if (ImGui::Selectable(actor.getName().c_str(), actor == selectedActor))
    selectedActor = actor;
  ImGui::Indent();
  for (system::Actor child : actor.getChildren())
    showActorHierarchy(child);
  ImGui::Unindent();
}

}  // namespace loki::editor
