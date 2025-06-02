#pragma once

#include <loki/system/modules/GameModule.hpp>
#include <loki/system/scheduler/UpdateTraits.hpp>

namespace loki::system {
class WindowModule;
class RendererModule;
}  // namespace loki::system

namespace loki::editor {
class ImGuiModule final : public system::GameModule {
 public:
  ~ImGuiModule() override;
  [[nodiscard]] const system::BaseUpdateTraits& getUpdateTraits() const override;
  void registerAsAService(core::ServiceRegistry& serviceRegistry) override;
  void init() override;
  void onInputReading(sf::Time delta) override;
  void onPreDebugRender(sf::Time delta) override;
  void onPostDebugRender(sf::Time delta) override;

 private:
  system::WindowModule* windowModule = nullptr;
  system::RendererModule* rendererModule = nullptr;
  bool isEnabled = false;
  bool drawDemo = true;

  LOKI_RTTI_CLASS_DECLARE(ImGuiModule)
};

}  // namespace loki::editor

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::editor::ImGuiModule, loki::system::GameModule)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::editor::ImGuiModule)
