#include "ImGuiModule.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

#include "render/RendererModule.hpp"

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
  // getService<system::RendererModule>().setDirectRender(false);
}

void ImGuiModule::update(sf::Time dt, UpdateSteps::InputReading) {
  if (!isEnabled)
    return;
  sf::RenderWindow& window = windowModule->getWindow().getRenderWindow();
  for (const sf::Event& event : windowModule->getEvents()) {
    ImGui::SFML::ProcessEvent(window, event);
  }
  ImGui::SFML::Update(window, dt);
  ImGuiDockNodeFlags DOCKING_FLAGS =
      ImGuiDockNodeFlags_NoDockingOverCentralNode | ImGuiDockNodeFlags_PassthruCentralNode;
  ImGui::DockSpaceOverViewport(0, nullptr, DOCKING_FLAGS);
  ImGui::ShowDemoWindow();
}

void ImGuiModule::update(sf::Time dt, UpdateSteps::EditorRender) {
  if (!isEnabled)
    return;
  ImGui::SFML::Render(windowModule->getWindow().getRenderWindow());
}

}  // namespace loki::editor
