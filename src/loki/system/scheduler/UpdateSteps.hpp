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
  DO(PreDebugRender)    /* for the clearing of the Window */      \
  DO(Render)            /* for the RendererModule */              \
  DO(DebugRender)       /* for the ImGuiModule */                 \
  DO(PostDebugRender)   /* for the ImGuiModule */                 \
  DO(PostRender)        /* for the display of the Window */

enum class UpdateStep {
#define LOKI_ADD_ENUMERATOR(StepName, ...) StepName,
  LOKI_SYSTEM_UPDATE_STEP_LIST(LOKI_ADD_ENUMERATOR)
#undef LOKI_ADD_ENUMERATOR
      Count
};

}  // namespace loki::system
