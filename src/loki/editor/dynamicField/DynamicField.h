#pragma once

#include <imgui.h>

#include "reflect/TypeInfo.h"

void DynamicField(const char* label, void* obj, const TypeInfo& typeInfo);

template <class T>
void DynamicField(const char* label, T& obj) {
  DynamicField(label, static_cast<void*>(&obj), getTypeInfo<T>());
}
