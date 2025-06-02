#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <loki/system/modules/GameModule.hpp>
#include <loki/system/render/RendererModule.hpp>

namespace loki::editor {

class DebugDrawModule final : public system::GameModule {
 public:
  ~DebugDrawModule() override = default;
  [[nodiscard]] const system::BaseUpdateTraits& getUpdateTraits() const override;
  void registerAsAService(core::ServiceRegistry& serviceRegistry) override;
  void init() override;

  void addRectangle(sf::FloatRect rect);

  void onPreDebugRender(sf::Time dt) override;
  void onPostDebugRender(sf::Time dt) override;

 private:
  system::RendererModule* rendererModule = nullptr;
  std::vector<sf::RectangleShape> rectangleShapes;

  LOKI_RTTI_CLASS_DECLARE(DebugDrawModule)
};

}  // namespace loki::editor

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::editor::DebugDrawModule, loki::system::GameModule)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::editor::DebugDrawModule)
