#pragma once

#include <cassert>
#include <print>
#include <type_traits>

#include <loki/core/reflection/classMacros.hpp>

namespace loki::core {

class BaseObject {
 public:
  virtual ~BaseObject() = default;
  [[nodiscard]] virtual const TypeInfo& getClassTypeInfo() const = 0;

  LOKI_REFLECTION_CLASS_DECLARE(BaseObject)
};

template <class T>
concept RuntimeObject = std::is_base_of_v<BaseObject, T>;

template <class T>
concept ReflectedRuntimeObject = Reflected<T> && RuntimeObject<T>;

inline void* asAncestor(void* ptr, const TypeInfo* ptrType, ClassId ancestorId) {
  void* result = ptr;
  while (true) {
    auto& currentClassInfo = std::get<ClassInfo>(ptrType->info);
    if (currentClassInfo.id == ancestorId)
      break;
    assert(currentClassInfo.parentType != nullptr);
    result = currentClassInfo.toParentType(result);
    ptrType = currentClassInfo.parentType;
  }
  return result;
}
}  // namespace loki::core

LOKI_REFLECTION_CLASS_BEGIN_NO_FACTORY(loki::core::BaseObject)
LOKI_REFLECTION_CLASS_END_RTTI(loki::core::BaseObject)