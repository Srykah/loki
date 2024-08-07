#pragma once

#include <loki/system/modules/GameModule.hpp>

namespace loki::editor {

class EditorModule final : public system::GameModule {
 public:
  ~EditorModule() override = default;
  void registerAsAService(core::ServiceRegistry& serviceRegistry) override;
  void init() override;

  LOKI_RTTI_CLASS_DECLARE(EditorModule)
  LOKI_GAMEMODULE_GET_UPDATE_TRAITS(EditorModule)
};

}  // namespace loki::editor

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::GameModule, loki::editor::EditorModule)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::editor::EditorModule)