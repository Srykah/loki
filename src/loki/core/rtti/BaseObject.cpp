#include <loki/core/reflection/TypeRegistry.hpp>
#include <loki/core/rtti/BaseObject.hpp>
#include <loki/core/services/ServiceRegistry.hpp>

namespace loki::core {

bool BaseObject::isAncestorOf(const ClassInfo& classInfo) {
  if (classInfo.parentType.empty()) {
    return false;
  }
  const auto* rootTypeInfo = &getTypeInfoFromId(classInfo.parentType);
  while (!rootTypeInfo->as<ClassInfo>().parentType.empty()) {
    rootTypeInfo = &getTypeInfoFromId(rootTypeInfo->as<ClassInfo>().parentType);
  }
  return rootTypeInfo->id == getTypeId<^^BaseObject>();
}

}  // namespace loki::core

LOKI_RTTI_CLASS_DEFINE(loki::core::BaseObject)