#pragma once

#include <SFML/Graphics/RenderTexture.hpp>

#include <loki/core/reflection/sfmlTypesInfo.hpp>
#include <loki/system/modules/GameModule.hpp>
#include <loki/system/render/RenderQueue.hpp>
#include <loki/system/scheduler/UpdateSteps.hpp>
#include <loki/system/window/WindowModule.hpp>

namespace loki::system {
class SceneManager;

class RendererModule final : public GameModule {
 public:
  ~RendererModule() override = default;
  [[nodiscard]] const BaseUpdateTraits& getUpdateTraits() const override;
  void registerAsAService(core::ServiceRegistry& serviceRegistry) override;
  void init() override;
  void onRender(sf::Time delta);

  const sf::RenderTexture& getTexture() const;

  void setDrawDebug(bool enable = true);

 private:
  sf::Vector2f internalResolution;
  SceneManager* sceneManager = nullptr;
  WindowModule* windowModule = nullptr;
  RenderQueue renderQueue;
  sf::RenderTexture renderTarget;

  bool drawDebug = false;

  LOKI_RTTI_CLASS_DECLARE(RendererModule)
};

}  // namespace loki::system

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::GameModule, loki::system::RendererModule)
LOKI_REFLECTION_CLASS_FIELD(internalResolution)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::system::RendererModule)

LOKI_UPDATE_TRAITS_BEGIN(loki::system::RendererModule)
LOKI_UPDATE_TRAITS_METHOD(Render, onRender)
LOKI_UPDATE_TRAITS_END()