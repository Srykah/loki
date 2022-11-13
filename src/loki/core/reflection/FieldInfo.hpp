#pragma once

#include "TypeInfo.hpp"

namespace loki::core {

struct FieldInfo {
  std::string_view name;
  std::string_view description;
  TypeInfo type;
};

}  // namespace loki::core