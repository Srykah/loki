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
  void registerAsAService(core::ServiceRegistry& serviceRegistry) override;
  void init() override;
  void update(sf::Time dt, UpdateSteps::Render);

  const sf::Texture& getTexture() const;

  void setDirectRender(bool enable = true);
  void setDrawDebug(bool enable = true);

 private:
  sf::Vector2u internalResolution;
  SceneManager* sceneManager = nullptr;
  WindowModule* windowModule = nullptr;
  RenderQueue renderQueue;
  sf::RenderTexture renderTarget;

  bool directRender = true;
  bool drawDebug = false;

  LOKI_RTTI_CLASS_DECLARE(RendererModule)
  LOKI_GAMEMODULE_GET_UPDATE_TRAITS(RendererModule)
};

}  // namespace loki::system

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::GameModule, loki::system::RendererModule)
LOKI_REFLECTION_CLASS_FIELD(internalResolution)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::system::RendererModule)