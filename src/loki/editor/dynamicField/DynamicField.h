#pragma once

#include <loki/core/reflection/TypeInfo.hpp>

namespace loki::editor {

void DynamicField(const char* label, void* obj, const core::TypeInfo& typeInfo);

template <class T>
void DynamicField(const char* label, T& obj) {
  DynamicField(label, static_cast<void*>(&obj), core::getTypeInfo<T>());
}

}  // namespace loki::editor