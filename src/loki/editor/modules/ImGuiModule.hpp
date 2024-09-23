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
  void onInputReading(sf::Time delta);
  void onPreDebugRender(sf::Time delta);
  void onPostDebugRender(sf::Time delta);

 private:
  system::WindowModule* windowModule = nullptr;
  system::RendererModule* rendererModule = nullptr;
  bool isEnabled = false;
  bool drawDemo = true;

  LOKI_RTTI_CLASS_DECLARE(ImGuiModule)
};

}  // namespace loki::editor

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::GameModule, loki::editor::ImGuiModule)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::editor::ImGuiModule)

LOKI_UPDATE_TRAITS_BEGIN(loki::editor::ImGuiModule)
LOKI_UPDATE_TRAITS_METHOD(InputReading, onInputReading)
LOKI_UPDATE_TRAITS_METHOD(PreDebugRender, onPreDebugRender)
LOKI_UPDATE_TRAITS_METHOD(PostDebugRender, onPostDebugRender)
LOKI_UPDATE_TRAITS_END()
