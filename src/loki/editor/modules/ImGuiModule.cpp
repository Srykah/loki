#include "ImGuiModule.hpp"

#include <imgui-SFML.h>
#include <imgui.h>
#include <imgui_internal.h>

#include <loki/system/render/RendererModule.hpp>
#include <loki/system/window/WindowModule.hpp>

namespace loki::editor {

LOKI_GAMEMODULE_GET_UPDATE_TRAITS(ImGuiModule)

ImGuiModule::~ImGuiModule() {
  if (isEnabled)
    ImGui::SFML::Shutdown();
}

void ImGuiModule::registerAsAService(core::ServiceRegistry& serviceRegistry) {
  serviceRegistry.registerService(*this);
}

void ImGuiModule::init() {
  windowModule = &getService<system::WindowModule>();
  rendererModule = &getService<system::RendererModule>();
  sf::RenderWindow& window = windowModule->getWindow().getRenderWindow();
  isEnabled = ImGui::SFML::Init(window);
  if (!isEnabled)
    return;
  auto& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void ImGuiModule::onInputReading(sf::Time delta) {
  if (!isEnabled)
    return;
  sf::RenderWindow& window = windowModule->getWindow().getRenderWindow();
  for (const sf::Event& event : windowModule->getEvents()) {
    ImGui::SFML::ProcessEvent(window, event);
  }
  ImGui::SFML::Update(window, delta);
}

void ImGuiModule::onPreDebugRender(sf::Time delta) {
  if (!isEnabled)
    return;
  const ImGuiID dockspaceId = ImGui::GetID("Main Dockspace");
  constexpr ImGuiDockNodeFlags DOCKING_FLAGS =
      ImGuiDockNodeFlags_NoDockingOverCentralNode | ImGuiDockNodeFlags_PassthruCentralNode;
  ImGui::DockSpaceOverViewport(dockspaceId, nullptr, DOCKING_FLAGS);
  const ImGuiDockNode* node = ImGui::DockBuilderGetCentralNode(dockspaceId);
  windowModule->getWindow().setRenderingArea({node->Pos, node->Size});
  if (drawDemo)
    ImGui::ShowDemoWindow();
}

void ImGuiModule::onPostDebugRender(sf::Time delta) {
  if (!isEnabled)
    return;
  sf::RenderWindow& window = windowModule->getWindow().getRenderWindow();
  ImGui::SFML::Render(window);
}

}  // namespace loki::editor
