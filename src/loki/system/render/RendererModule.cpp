#include "RendererModule.hpp"

#include <loki/core/services/ServiceRegistry.hpp>
#include <loki/system/ecs/Component.hpp>
#include <loki/system/ecs/ComponentTraits.hpp>
#include <loki/system/render/RenderQueue.hpp>
#include <loki/system/scene/SceneManager.hpp>
#include <loki/system/window/WindowModule.hpp>

namespace loki::system {

LOKI_GAMEMODULE_GET_UPDATE_TRAITS(RendererModule)

void RendererModule::registerAsAService(core::ServiceRegistry& serviceRegistry) {
  serviceRegistry.registerService(*this);
}

void RendererModule::init() {
  sceneManager = &getService<SceneManager>();
  windowModule = &getService<WindowModule>();
  renderTarget.create(internalResolution.x, internalResolution.y);
  windowModule->getWindow().setInternalResolution(internalResolution);
}

void RendererModule::onRender(sf::Time delta) {
  // render the queue
  renderTarget.clear();
  renderTarget.draw(renderQueue);
  renderTarget.display();

  // todo remove direct dependency ?
  sf::Sprite sprite;
  sprite.setTexture(renderTarget.getTexture());
  windowModule->getWindow().draw(sprite);
}

RenderQueue& RendererModule::getRenderQueue() {
  return renderQueue;
}

const sf::RenderTexture& RendererModule::getTexture() const {
  return renderTarget;
}

void RendererModule::setDrawDebug(bool enable) {
  drawDebug = enable;
}

}  // namespace loki::system
