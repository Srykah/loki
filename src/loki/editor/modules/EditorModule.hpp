#pragma once

#include <loki/system/modules/GameModule.hpp>

namespace loki::editor {

class EditorModule final : public system::GameModule {
 public:
  ~EditorModule() override = default;
  void registerAsAService(core::ServiceRegistry& serviceRegistry) override;
  void init() override;
  void update(system::UpdateStep updateStep, sf::Time dt) override;

  LOKI_RTTI_CLASS_DECLARE(EditorModule)
};

}  // namespace loki::editor

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::system::GameModule, loki::editor::EditorModule)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::editor::EditorModule)