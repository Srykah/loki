#pragma once

#include <cassert>
#include <print>

#include <loki/core/reflection/classMacros.hpp>
#include <loki/core/rtti/rttiMacros.hpp>

namespace loki::core {

class BaseObject {
 public:
  virtual ~BaseObject() = default;
  [[nodiscard]] virtual const TypeInfo& getClassTypeInfo() const = 0;

  LOKI_REFLECTION_CLASS_DECLARE(BaseObject)
};

}  // namespace loki::core

LOKI_REFLECTION_CLASS_BEGIN_NO_FACTORY(loki::core::BaseObject)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::core::BaseObject)