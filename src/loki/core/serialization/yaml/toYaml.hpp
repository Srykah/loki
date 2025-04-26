#pragma once

#include <yaml-cpp/yaml.h>

#include <loki/core/reflection/TypeInfo.hpp>

namespace loki::core {

void toYaml(YAML::Emitter& emitter, const void* obj, const TypeInfo& typeInfo);

template <class T>
void toYaml(YAML::Emitter& emitter, const T& obj) {
  toYaml(emitter, static_cast<const void*>(&obj), getTypeInfo<T>());
}
}  // namespace loki::core

namespace YAML {

template <loki::core::Reflected T>
Emitter& operator<<(Emitter& emitter, const T& t) {
  loki::core::toYaml(emitter, t);
  return emitter;
}

}  // namespace YAML