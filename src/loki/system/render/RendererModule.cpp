#include "RendererModule.hpp"

#include <loki/core/services/ServiceRegistry.hpp>
#include <loki/system/ecs/Component.hpp>
#include <loki/system/ecs/ComponentTraits.hpp>
#include <loki/system/render/RenderQueue.hpp>
#include <loki/system/scene/SceneManager.hpp>

#include "loki/system/window/WindowModule.hpp"

namespace loki::system {

void RendererModule::registerAsAService(core::ServiceRegistry& serviceRegistry) {
  serviceRegistry.registerService(*this);
}

void RendererModule::init() {
  sceneManager = &getService<SceneManager>();
  windowModule = &getService<WindowModule>();
  renderTarget.create(internalResolution.x, internalResolution.y);
}

void RendererModule::update(UpdateStep updateStep, sf::Time dt) {
  renderQueue.clear();
  assert(sceneManager);

  {
    auto compTraitsFilter = [](const BaseComponentTraits& compTraits) { return compTraits.isDrawable(); };
    auto compVisitor = [this](const BaseComponentTraits& compTraits, void* compPtr) {
      // get as a Component
      const auto& comp = compTraits.getAsComponent(compPtr);
      // if it is not ready, ignore it
      if (comp.getStatus() != Component::Status::READY)
        return;
      if (auto* drawable = compTraits.getAsDrawable(comp)) {
        // if the component is a Drawable, add it to the render queue
        renderQueue.registerDrawable(drawable->getDrawOrder(), drawable);
      }
    };
    sceneManager->getCurrentScene()->visitComponents(compTraitsFilter, compVisitor);
  }

  if (drawDebug) {
    auto compTraitsFilter = [](const BaseComponentTraits& compTraits) { return compTraits.isDebugDrawable(); };
    auto compVisitor = [this](const BaseComponentTraits& compTraits, void* compPtr) {
      // get as a Component
      const auto& comp = compTraits.getAsComponent(compPtr);
      // if it is not ready, ignore it
      if (comp.getStatus() != Component::Status::READY)
        return;
      if (auto* debugDrawable = compTraits.getAsDebugDrawable(comp)) {
        // if the component is a DebugDrawable, add it to the render queue
        renderQueue.registerDebugDrawable(debugDrawable->getDebugDrawOrder(), debugDrawable);
      }
    };
    sceneManager->getCurrentScene()->visitComponents(compTraitsFilter, compVisitor);
  }

  // render the queue
  renderTarget.draw(renderQueue);

  // todo remove direct dependency
  sf::Sprite sprite;
  sprite.setTexture(renderTarget.getTexture());
  sprite.setPosition(0.f, renderTarget.getSize().y);
  sprite.setScale(1.f, -1.f);
  windowModule->getWindow().draw(sprite);
}

}  // namespace loki::system
