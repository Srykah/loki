#pragma once

namespace loki::system {

#define LOKI_SYSTEM_UPDATE_STEP_LIST(DO)                          \
  DO(InputPolling)      /* for the event polling of the Window */ \
  DO(InputReading)      /* for the InputModule & ImGuiModule */   \
  DO(PrePhysics)        /* for character controllers */           \
  DO(PhysicsSimulation) /* for the PhysicsWorld */                \
  DO(PhysicsResult)     /* for the PhysicsBodies */               \
  DO(Default)           /* for pretty much everything */          \
  DO(PreRender)         /* for the clearing of the Window */      \
  DO(Render)            /* for the RendererModule */              \
  DO(DebugMenuRender)   /* for the ImGuiModule */                 \
  DO(PostRender)        /* for the display of the Window */

enum class UpdateStep {
#define LOKI_ADD_ENUMERATOR(StepName, ...) StepName,
  LOKI_SYSTEM_UPDATE_STEP_LIST(LOKI_ADD_ENUMERATOR)
#undef LOKI_ADD_ENUMERATOR
      Count
};

template <UpdateStep Step>
struct UpdateStepTag {
  static constexpr UpdateStep step = Step;
};

}  // namespace loki::system

namespace loki::UpdateSteps {

#define LOKI_INTRODUCE_TAG_ALIAS(StepName, ...) using StepName = system::UpdateStepTag<system::UpdateStep::StepName>;
LOKI_SYSTEM_UPDATE_STEP_LIST(LOKI_INTRODUCE_TAG_ALIAS)
#undef LOKI_INTRODUCE_TAG_ALIAS

}  // namespace loki::UpdateSteps
