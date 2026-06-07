#pragma once

#include <cassert>
#include <print>

#include <loki/core/reflection/reflectionUtils.hpp>
#include <loki/core/rtti/rttiMacros.hpp>

namespace loki::core {

struct TypeInfo;
struct ClassInfo;

class[[= loki::reflect]] BaseObject {
 public:
  virtual ~BaseObject() = default;
  [[nodiscard]] virtual const TypeInfo& getTypeInfo() const = 0;

  [[nodiscard]] static bool isAncestorOf(const ClassInfo& classInfo);
};

template <class T>
concept RuntimeObject = std::is_base_of_v<BaseObject, T>;

}  // namespace loki::core
