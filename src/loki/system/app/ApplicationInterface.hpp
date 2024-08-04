#pragma once

#include <memory>

#include <loki/core/rtti/BaseObject.hpp>

namespace loki::system {
class GameModule;

class ApplicationInterface : public core::BaseObject {
 public:
  virtual std::span<std::unique_ptr<GameModule>> getGameModules() = 0;
  virtual void exit() = 0;

  LOKI_RTTI_CLASS_DECLARE(ApplicationInterface)
};

}  // namespace loki::system

LOKI_REFLECTION_CLASS_BEGIN_NO_FACTORY(loki::system::ApplicationInterface)
LOKI_REFLECTION_CLASS_PARENT(loki::system::ApplicationInterface, loki::core::BaseObject)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::system::ApplicationInterface)
