#include "Scheduler.hpp"

#include <loki/core/services/ServiceRegistry.hpp>
#include <loki/system/app/ApplicationInterface.hpp>
#include <loki/system/ecs/Component.hpp>
#include <loki/system/ecs/ComponentTraits.hpp>
#include <loki/system/modules/GameModule.hpp>
#include <loki/system/scene/SceneManager.hpp>

namespace loki::system {

Scheduler::Scheduler(ApplicationInterface& app, SceneManager& sceneManager) : app(app), sceneManager(sceneManager) {}

void Scheduler::init() {
  for (auto& gameModule : app.getGameModules())
    gameModule->init();
}

void Scheduler::update(sf::Time dt) {
  for (unsigned int step = 0; step < 64; ++step) {
    UpdateStep updateStep = static_cast<UpdateStep>(1u << step);
    for (auto& gameModule : app.getGameModules()) {
      if (contains(gameModule->getUpdateStep(), updateStep))
        gameModule->update(updateStep, dt);
    }

    auto compTraitsFilter = [updateStep](const BaseComponentTraits& compTraits) {
      return contains(compTraits.getUpdateStep(), updateStep);
    };
    auto compVisitor = [updateStep, dt](const BaseComponentTraits& compTraits, void* compPtr) {
      // get the component as a Component*
      auto& comp = compTraits.getAsComponent(compPtr);
      // update it (could do all steps at once)
      if (comp.getStatus() == Component::Status::CREATED)
        comp.startInit();
      if (comp.getStatus() == Component::Status::LOADING_RESOURCES)
        return;  // wait
      if (comp.getStatus() == Component::Status::RESOURCES_LOADED)
        comp.finalizeInit();
      if (comp.getStatus() == Component::Status::READY)
        comp.update(updateStep, dt);
      // if (comp.getStatus() == Component::Status::DEINIT) // todo
    };

    sceneManager.getCurrentScene()->visitComponents(compTraitsFilter, compVisitor);
  }
}

}  // namespace loki::system
