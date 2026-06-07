#include "TypeRegistry.hpp"

#include <loki/core/services/ServiceRegistry.hpp>

namespace loki::core {

void TypeRegistry::registerType(TypeInfo&& typeInfo) {
  auto [it, inserted] = typeIdToTypeInfo.emplace(typeInfo.id, std::move(typeInfo));
  if (!inserted) {
    throw std::runtime_error("Type with the same id already registered!");
  }
}

const TypeInfo& TypeRegistry::getFromId(const TypeId& id) const {
  auto it = typeIdToTypeInfo.find(id);
  if (it == typeIdToTypeInfo.end()) {
    throw std::runtime_error("Type not found in registry!");
  }
  return it->second;
}

void* TypeRegistry::asAncestor(void* ptr, const TypeInfo* ptrType, const TypeId& ancestorId) {
  void* result = ptr;
  while (true) {
    if (ptrType->id == ancestorId)
      break;
    auto& currentClassInfo = std::get<ClassInfo>(ptrType->info);
    assert(!currentClassInfo.parentType.empty());
    result = currentClassInfo.toParentType(result);
    ptrType = &getFromId(currentClassInfo.parentType);
  }
  return result;
}

}  // namespace loki::core

LOKI_RTTI_CLASS_DEFINE(loki::core::TypeRegistry)

namespace loki {

const core::TypeInfo& getTypeInfoFromId(const core::TypeId& id) {
  return getService<core::TypeRegistry>().getFromId(id);
}
}  // namespace loki
