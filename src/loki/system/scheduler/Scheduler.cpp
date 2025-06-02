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

void Scheduler::setPaused(bool isPaused) {
  paused = isPaused;
}

bool Scheduler::isPaused() const {
  return paused;
}

void Scheduler::handleComponentsLifecycle() {
  auto compVisitor = [](const BaseComponentTraits& compTraits, void* compPtr) {
    auto& comp = compTraits.getAsComponent(compPtr);
    if (comp.getLifeCycleStep() == LifeCycleStep::Created) {
      comp.onBeginInit();
      comp.setLifeCycleStep(comp.getResourceLoadingStatus() == ResourceLoadingStatus::Loading
                                ? LifeCycleStep::LoadingDependencies
                                : LifeCycleStep::DependenciesLoaded);
    }
    if (comp.getLifeCycleStep() == LifeCycleStep::LoadingDependencies &&
        comp.getResourceLoadingStatus() == ResourceLoadingStatus::Loaded) {
      comp.onDependenciesLoaded();
      comp.setLifeCycleStep(LifeCycleStep::DependenciesLoaded);
    }
    if (comp.getLifeCycleStep() == LifeCycleStep::DependenciesLoaded) {
      comp.onEndInit();
      comp.setLifeCycleStep(LifeCycleStep::Ready);
    }
  };
  sceneManager.getCurrentScene()->visitComponents(compVisitor);
  auto activationVisitor = [](Actor actor) {
    bool areAllComponentsReady = true;
    actor.visitComponents([&](const BaseComponentTraits& compTraits, void* compPtr) {
      auto& comp = compTraits.getAsComponent(compPtr);
      if (comp.getLifeCycleStep() != LifeCycleStep::Ready)
        areAllComponentsReady = false;
    });
    if (areAllComponentsReady) {
      actor.visitComponents([&](const BaseComponentTraits& compTraits, void* compPtr) {
        auto& comp = compTraits.getAsComponent(compPtr);
        comp.onActivate();
        comp.setLifeCycleStep(LifeCycleStep::Active);
      });
    }
  };
  sceneManager.getCurrentScene()->visitActors(activationVisitor);
}

void Scheduler::runUpdateSteps(sf::Time dt) {
  for (std::underlying_type_t<UpdateStep> step = 0; step < std::to_underlying(UpdateStep::Count); ++step) {
    UpdateStep updateStep = static_cast<UpdateStep>(step);
    runUpdateStepForGameModules(dt, updateStep);
    if (!paused)
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
    if (comp.getLifeCycleStep() == LifeCycleStep::Active)
      compTraits.getUpdateTraits().runUpdateStep(compPtr, dt, updateStep);
  };
  sceneManager.getCurrentScene()->visitComponents(compTraitsFilter, compVisitor);
}

}  // namespace loki::system
