#pragma once

#include <loki/core/reflection/TypeInfo.hpp>

namespace loki::editor {

bool DynamicField(const char* label, void* obj, const core::TypeInfo& typeInfo);

template <class T>
bool DynamicField(const char* label, T& obj) {
  return DynamicField(label, static_cast<void*>(&obj), core::getTypeInfo<T>());
}

}  // namespace loki::editor