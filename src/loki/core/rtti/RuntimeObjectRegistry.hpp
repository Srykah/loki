#pragma once

#include <cassert>

#include <loki/core/reflection/TypeInfo.hpp>
#include <loki/core/rtti/BaseObject.hpp>
#include <loki/core/rtti/rttiConcepts.hpp>

namespace loki::core {

class RuntimeObjectRegistry : public BaseObject {
 public:
  template <ReflectedRuntimeObject T>
  void registerClass() {
    const TypeInfo& typeInfo = getTypeInfo<T>();
    assert(std::holds_alternative<ClassInfo>(typeInfo.info));
    const auto& classInfo = std::get<ClassInfo>(typeInfo.info);
    typeIdToTypeInfo.emplace(classInfo.id, &typeInfo);
  }

  [[nodiscard]] const TypeInfo* getRuntimeTypeInfo(ClassId id) const;
  [[nodiscard]] TmpObj instantiate(ClassId id,
                                   void* ctx = nullptr,
                                   TmpObj::Ownership ownership = TmpObj::Ownership::Default);

 private:
  std::unordered_map<ClassId, const TypeInfo*> typeIdToTypeInfo;

  LOKI_RTTI_CLASS_DECLARE(RuntimeObjectRegistry)
};

}  // namespace loki::core

LOKI_REFLECTION_CLASS_BEGIN_CHILD(loki::core::BaseObject, loki::core::RuntimeObjectRegistry)
LOKI_REFLECTION_CLASS_END()
LOKI_RTTI_CLASS_DEFINE(loki::core::RuntimeObjectRegistry)
