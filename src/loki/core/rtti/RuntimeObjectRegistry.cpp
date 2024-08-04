#include "RuntimeObjectRegistry.hpp"

namespace loki::core {

const TypeInfo* RuntimeObjectRegistry::getRuntimeTypeInfo(ClassId id) const {
  auto it = typeIdToTypeInfo.find(id);
  return it != typeIdToTypeInfo.end() ? it->second : nullptr;
}

TmpObj RuntimeObjectRegistry::instantiate(ClassId id, void* ctx, TmpObj::Ownership ownership) {
  return getRuntimeTypeInfo(id)->factory(ctx, ownership);
}

}  // namespace loki::core