#include "Scheduler.hpp"

#include <loki/core/services/ServiceRegistry.hpp>
#include <loki/system/app/ApplicationInterface.hpp>
#include <loki/system/ecs/Component.hpp>
#include <loki/system/ecs/ComponentTraits.hpp>
#include <loki/system/modules/GameModule.hpp>
#include <loki/system/scene/SceneManager.hpp>

namespace loki::system {

Scheduler::Scheduler(ApplicationInterface& app, SceneManager& sceneManager) : app(app), sceneManager(sceneManager) {}

void Scheduler::initGameModules() {
  for (auto& gameModule : app.getGameModules())
    gameModule->init();
}

void Scheduler::update(sf::Time dt) {
  handleComponentsLifecycle();
  runUpdateSteps(dt);
  // todo deinit
}

void Scheduler::handleComponentsLifecycle() {
  auto compVisitor = [](const BaseComponentTraits& compTraits, void* compPtr) {
    auto& comp = compTraits.getAsComponent(compPtr);
    if (comp.getStatus() == Component::Status::CREATED)
      comp.startInit();
    if (comp.getStatus() == Component::Status::RESOURCES_LOADED)
      comp.finalizeInit();
  };
  sceneManager.getCurrentScene()->visitComponents(compVisitor);
}

void Scheduler::runUpdateSteps(sf::Time dt) {
  for (std::underlying_type_t<UpdateStep> step = 0; step < std::to_underlying(UpdateStep::Count); ++step) {
    UpdateStep updateStep = static_cast<UpdateStep>(step);
    runUpdateStepForGameModules(dt, updateStep);
    runUpdateStepForComponents(dt, updateStep);
  }
}

void Scheduler::runUpdateStepForGameModules(sf::Time dt, UpdateStep updateStep) {
  for (auto& gameModule : app.getGameModules()) {
    if (gameModule->getUpdateTraits().hasUpdateStep(updateStep))
      gameModule->getUpdateTraits().runUpdateStep(gameModule.get(), dt, updateStep);
  }
}
void Scheduler::runUpdateStepForComponents(sf::Time dt, UpdateStep updateStep) {
  auto compTraitsFilter = [updateStep](const BaseComponentTraits& compTraits) {
    return compTraits.getUpdateTraits().hasUpdateStep(updateStep);
  };
  auto compVisitor = [updateStep, dt](const BaseComponentTraits& compTraits, void* compPtr) {
    auto& comp = compTraits.getAsComponent(compPtr);
    if (comp.getStatus() == Component::Status::READY)
      compTraits.getUpdateTraits().runUpdateStep(compPtr, dt, updateStep);
  };
  sceneManager.getCurrentScene()->visitComponents(compTraitsFilter, compVisitor);
}

}  // namespace loki::system
