#include "EditorModule.hpp"

#include <imgui.h>

#include <loki/core/reflection/sfmlTypesInfo.hpp>
#include <loki/system/box/BoundingBoxComponent.hpp>
#include <loki/system/ecs/Component.hpp>
#include <loki/system/ecs/ComponentTraits.hpp>
#include <loki/system/scene/SceneManager.hpp>
#include <loki/editor/dynamicField/DynamicField.hpp>

namespace loki::editor {

LOKI_GAMEMODULE_GET_UPDATE_TRAITS(EditorModule)

void EditorModule::registerAsAService(core::ServiceRegistry& serviceRegistry) {
  serviceRegistry.registerService(*this);
}

void EditorModule::init() {
  debugDrawModule = &getService<DebugDrawModule>();
  sceneManager = &getService<system::SceneManager>();
}

void EditorModule::onUpdate(sf::Time dt) {
  showActorBoundingBoxes();
}

void EditorModule::onDebugRender(sf::Time delta) {
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

void EditorModule::showActorBoundingBoxes() {
  sceneManager->getCurrentScene()->visitComponents(
      [](const system::BaseComponentTraits& compTraits) {
        return std::get<core::ClassInfo>(compTraits.getTypeInfo().info).id ==
               std::get<core::ClassInfo>(core::getTypeInfo<system::BoundingBoxComponent>().info).id;
      },
      [this](const system::BaseComponentTraits& compTraits, const void* obj) {
        debugDrawModule->addRectangle(static_cast<const system::BoundingBoxComponent*>(obj)->getGlobalBox());
      });
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
