#pragma once

#include "TypeInfo.hpp"

namespace loki::core {

template <>
const TypeInfo* getTypeInfo<class BaseObject>();

class BaseObject {
 public:
  virtual ~BaseObject() = default;
  [[nodiscard]] virtual const TypeInfo* getTypeInfo() const { return ::loki::core::getTypeInfo<BaseObject>(); }
};

template <>
const TypeInfo* getTypeInfo<BaseObject>() {
  static TypeInfo typeInfo{.index = typeid(BaseObject),
                           .name = "loki::core::BaseObject",
                           .description = "Base object for factories based on reflection",
                           .parents = {},
                           .fields = {}};
  return &typeInfo;
}

}  // namespace loki::core