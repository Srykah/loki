#pragma once

#include <ryml_std.hpp>
#include <ryml.hpp>

#include <loki/core/reflection/TypeInfo.hpp>

namespace loki::core {

void toYaml(ryml::NodeRef destNode, const void* obj, const TypeInfo& typeInfo);

template <class T>
void toYaml(ryml::NodeRef destNode, const T& obj) {
  toYaml(destNode, static_cast<const void*>(&obj), getTypeInfo<T>());
}

}  // namespace loki::core
