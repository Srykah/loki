#pragma once

#include <loki/system/ecs/Actor.hpp>
#include <loki/system/modules/GameModule.hpp>

namespace loki::system {
class SceneManager;
}

namespace loki::editor {

class EditorModule final : public system::GameModule {
 public:
  ~EditorModule() override = default;
  [[nodiscard]] const system::BaseUpdateTraits& getUpdateTraits() const override;
  void registerAsAService(core::ServiceRegistry& serviceRegistry) override;
  void init() override;
  void onDebugRender(sf::Time dt);

 private:
  void showScenePanel();
  void showActorPanel();

  void showActorHierarchy(system::Actor actor);

 private:
  system::SceneManager* sceneManager = nullptr;
  system::Actor selectedActor;

  LOKI_RTTI_CLASS_DECLARE(EditorModule)
};

}  // namespace loki::editor

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::GameModule, loki::editor::EditorModule)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::editor::EditorModule)

LOKI_UPDATE_TRAITS_BEGIN(loki::editor::EditorModule)
LOKI_UPDATE_TRAITS_METHOD(DebugRender, onDebugRender)
LOKI_UPDATE_TRAITS_END()