#pragma once

#include <string>

#include <loki/core/reflection/TypeInfo.hpp>

namespace loki::core {

void toString(std::string& str, const void* obj, const TypeInfo& typeInfo);

template <class T>
void toString(std::string& str, const T& obj) {
  toString(str, static_cast<const void*>(&obj), getTypeInfo<T>());
}

}