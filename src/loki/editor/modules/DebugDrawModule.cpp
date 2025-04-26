#include "DebugDrawModule.hpp"

namespace loki::editor {

LOKI_GAMEMODULE_GET_UPDATE_TRAITS(DebugDrawModule)

void DebugDrawModule::registerAsAService(core::ServiceRegistry& serviceRegistry) {
  serviceRegistry.registerService(*this);
}
void DebugDrawModule::init() {
  rendererModule = &getService<system::RendererModule>();
}

void DebugDrawModule::addRectangle(sf::FloatRect rect) {
  auto& newRect = rectangleShapes.emplace_back();
  newRect.setSize(rect.getSize());
  newRect.setPosition(rect.getPosition());
  newRect.setFillColor(sf::Color::Transparent);
  newRect.setOutlineColor(sf::Color::Red);
  newRect.setOutlineThickness(-1.f);
}

void DebugDrawModule::onPreDebugRender(sf::Time delta) {
  for (const auto& rect : rectangleShapes)
    rendererModule->getRenderQueue().registerDrawable(&rect, {}, true);
}

void DebugDrawModule::onPostDebugRender(sf::Time delta) {
  for (const auto& rect : rectangleShapes)
    rendererModule->getRenderQueue().unregisterDrawable(&rect);

  rectangleShapes.clear();
}

}  // namespace loki::editor
