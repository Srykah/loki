#pragma once

#include "TypeInfo.hpp"

namespace loki::core {

class BaseObject {
 public:
  virtual ~BaseObject() = default;
  [[nodiscard]] virtual const TypeInfo& getTypeInfo() const {
    static const TypeInfo typeInfo = {.typeInfo = typeid(BaseObject),
                                      .name = "loki::core::BaseObject",
                                      .description = "Base object for factories based on reflection",
                                      .parents = {},
                                      .fields = {}};
    return typeInfo;
  }
};

}  // namespace loki::core