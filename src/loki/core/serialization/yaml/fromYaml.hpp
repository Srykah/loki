#pragma once

#include <string>

#include <yaml-cpp/yaml.h>

#include <loki/core/reflection/TypeInfo.hpp>

namespace loki::core {

void fromYaml(const YAML::Node& node, void* obj, const TypeInfo& typeInfo);

template <class T>
void fromYaml(const YAML::Node& node, T& obj) {
  fromYaml(node, static_cast<void*>(&obj), getTypeInfo<T>());
}

}