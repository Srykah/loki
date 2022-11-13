#pragma once

#include <span>
#include <string_view>

namespace loki::core {

struct FieldInfo;

struct TypeInfo {
  const std::type_info& typeInfo;
  std::string_view name;
  std::string_view description;
  std::span<TypeInfo> parents;
  std::span<FieldInfo> fields;
};

template <class T>
constexpr TypeInfo getTypeInfo();

template <>
constexpr TypeInfo getTypeInfo<bool>() {
  return {
      .typeInfo = typeid(bool), .name = "bool", .description = "A true or false value", .parents = {}, .fields = {}};
}

}  // namespace loki::core