#pragma once

#include <span>
#include <string_view>
#include <typeindex>

#include <nlohmann/json.hpp>

namespace loki::core {

struct FieldInfo;

struct TypeInfo {
  std::type_index index;
  std::string_view name;
  std::string_view description;
  std::vector<const TypeInfo*> parents;
  std::vector<FieldInfo> fields;
  unsigned int version = 1;

  auto operator<=>(const TypeInfo& other) const { return index <=> other.index; }
};

struct FieldInfo {
  const TypeInfo* type;
  std::string_view name;
  std::string_view description;
};

template <class T>
const TypeInfo* getTypeInfo();

template <class T>
concept Reflected = requires { getTypeInfo<T>(); };

}  // namespace loki::core