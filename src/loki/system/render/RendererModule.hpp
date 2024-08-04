#pragma once

#include <SFML/Graphics/RenderTexture.hpp>

#include <loki/core/reflection/sfmlTypesInfo.hpp>
#include <loki/system/modules/GameModule.hpp>
#include <loki/system/render/RenderQueue.hpp>

namespace loki::system {
class SceneManager;

class RendererModule final : public GameModule {
 public:
  ~RendererModule() override = default;
  void registerAsAService(core::ServiceRegistry& serviceRegistry) override;
  void init() override;
  void update(sf::Time dt) override;

 private:
  sf::Vector2u internalResolution;
  SceneManager* sceneManager = nullptr;
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