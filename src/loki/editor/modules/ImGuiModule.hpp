#pragma once

#include <loki/system/modules/GameModule.hpp>
#include <loki/system/scheduler/UpdateSteps.hpp>

namespace loki::system {
class WindowModule;
class RendererModule;
}  // namespace loki::system

namespace loki::editor {
class ImGuiModule final : public system::GameModule {
 public:
  ~ImGuiModule() override;
  void registerAsAService(core::ServiceRegistry& serviceRegistry) override;
  void init() override;
  void update(sf::Time dt, UpdateSteps::InputReading);
  void update(sf::Time dt, UpdateSteps::PreRender);
  void update(sf::Time dt, UpdateSteps::DebugMenuRender);

 private:
  system::WindowModule* windowModule = nullptr;
  system::RendererModule* rendererModule = nullptr;
  bool isEnabled = false;
  bool drawDemo = true;

  LOKI_RTTI_CLASS_DECLARE(ImGuiModule)
  LOKI_GAMEMODULE_GET_UPDATE_TRAITS(ImGuiModule)
};

}  // namespace loki::editor

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::GameModule, loki::editor::ImGuiModule)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::editor::ImGuiModule)
