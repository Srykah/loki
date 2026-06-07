#pragma once

#include <string>

#include <ryml.hpp>
#include <ryml_std.hpp>

#include <loki/core/reflection/TypeRegistry.hpp>

namespace loki::core {

void fromYaml(const ryml::ConstNodeRef& node, void* obj, const TypeInfo& typeInfo);

template <class T>
void fromYaml(const ryml::ConstNodeRef& node, T& obj) {
  fromYaml(node, static_cast<void*>(&obj), getTypeInfo<T>());
}

}  // namespace loki::core