#pragma once

#include <string>

#include <yaml-cpp/yaml.h>

#include <loki/core/reflection/TypeInfo.hpp>

namespace loki::core {

void toYaml(YAML::Node& node, const void* obj, const TypeInfo& typeInfo);

template <class T>
void toYaml(YAML::Node& node, const T& obj) {
  toYaml(node, static_cast<const void*>(&obj), getTypeInfo<T>());
}
}