#pragma once

#include "FieldInfo.hpp"
#include "TypeInfo.hpp"

namespace loki::core {

template <>
constexpr TypeInfo getTypeInfo<bool>() {
  return {
      .typeInfo = &typeid(bool), .name = "bool", .description = "A true or false value", .parents = {}, .fields = {}};
}

}  // namespace loki::core