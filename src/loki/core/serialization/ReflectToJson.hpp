#pragma once

#include <nlohmann/json.hpp>

#include <loki/core/reflection/TypeInfo.hpp>

namespace nlohmann {

template <loki::core::Reflected T>
struct adl_serializer<T> {
  void from_json(const json& j, T& t) {
    const loki::core::TypeInfo* typeInfo = loki::core::getTypeInfo<T>();
    for (const auto& field : typeInfo->fields) {
      field.deserializer(reinterpret_cast<void*>(&t), j.at(std::string(field.name)));
    }
  }

  void to_json(json& j, const T& t) {
    const loki::core::TypeInfo* typeInfo = loki::core::getTypeInfo<T>();
    for (const auto& field : typeInfo->fields) {
      field.serializer(reinterpret_cast<const void*>(&t), j[std::string(field.name)]);
    }
  }
};

}  // namespace nlohmann