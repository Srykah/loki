#include "ImGuiModule.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

namespace loki::editor {

ImGuiModule::~ImGuiModule() {
  if (isEnabled)
    ImGui::SFML::Shutdown();
}

void ImGuiModule::registerAsAService(core::ServiceRegistry& serviceRegistry) {
  serviceRegistry.registerService(*this);
}

void ImGuiModule::init() {
  windowModule = &getService<system::WindowModule>();
  sf::RenderWindow& window = windowModule->getWindow().getRenderWindow();
  isEnabled = ImGui::SFML::Init(window);
  if (!isEnabled)
    return;
  auto& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void ImGuiModule::update(system::UpdateStep updateStep, sf::Time dt) {
  if (!isEnabled)
    return;
  sf::RenderWindow& window = windowModule->getWindow().getRenderWindow();
  if (updateStep == system::UpdateStep::InputReading) {
    for (const sf::Event& event : windowModule->getEvents())
      ImGui::SFML::ProcessEvent(window, event);
    ImGui::SFML::Update(window, dt);
    ImGui::DockSpaceOverViewport(0, nullptr,
                                 ImGuiDockNodeFlags_NoDockingOverCentralNode | ImGuiDockNodeFlags_PassthruCentralNode);
    ImGui::ShowDemoWindow();
  } else if (updateStep == system::UpdateStep::EditorRender) {
    ImGui::SFML::Render(window);
  }
}

}  // namespace loki::editor
