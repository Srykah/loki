#pragma once

#include <loki/system/ecs/Actor.hpp>
#include <loki/system/modules/GameModule.hpp>
#include <loki/editor/modules/DebugDrawModule.hpp>

namespace loki::system {
class Scheduler;
class SceneManager;
}  // namespace loki::system

namespace loki::editor {

class EditorModule final : public system::GameModule {
 public:
  ~EditorModule() override = default;
  [[nodiscard]] const system::BaseUpdateTraits& getUpdateTraits() const override;
  void registerAsAService(core::ServiceRegistry& serviceRegistry) override;
  void init() override;
  void onUpdate(sf::Time dt);
  void onDebugRender(sf::Time dt);

 private:
  void showMenuBar();
  void showSceneTabs();
  void showScenePanel();
  void showActorPanel();
  void showActorBoundingBoxes();

  void showActorHierarchy(system::Actor actor);

 private:
  DebugDrawModule* debugDrawModule = nullptr;
  system::SceneManager* sceneManager = nullptr;
  system::Scheduler* scheduler = nullptr;
  system::Actor selectedActor;

  LOKI_RTTI_CLASS_DECLARE(EditorModule)
};

}  // namespace loki::editor

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::editor::EditorModule, loki::system::GameModule)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::editor::EditorModule)
