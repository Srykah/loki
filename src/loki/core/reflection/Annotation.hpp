#pragma once

#include <meta>
#include <string>

#include <loki/core/reflection/reflectionUtils.hpp>

namespace loki::core {

using TypeId = std::string;
using NameId = std::string;

struct Annotation {
  enum AppliesTo {
    Nothing = 0,
    Class = 1 << 0,
    Field = 1 << 1,
    Enum = 1 << 2,
    EnumValue = 1 << 3,
  };
  virtual ~Annotation() = default;
  virtual const TypeId& getTypeId() const = 0;
};

#define LOKI_ANNOT_GET_TYPE_ID(Class)                            \
  const TypeId& getTypeId() const override {                     \
    static const TypeId id = ::loki::core::getTypeId<^^Class>(); \
    return id;                                                   \
  }

struct SerializeFlowStyle final : public Annotation {
  static constexpr AppliesTo appliesTo = AppliesTo::Class;
  struct Data {};
  SerializeFlowStyle(const Data& data) {}
  LOKI_ANNOT_GET_TYPE_ID(SerializeFlowStyle)
};
static constexpr SerializeFlowStyle::Data flowStyle;

struct SerializeBlockStyle final : public Annotation {
  static constexpr AppliesTo appliesTo = AppliesTo::Class;
  struct Data {};
  SerializeBlockStyle(const Data& data) {}
  LOKI_ANNOT_GET_TYPE_ID(SerializeBlockStyle)
};
static constexpr SerializeBlockStyle::Data blockStyle;

struct ReflectAsMember final : public Annotation {
  static constexpr AppliesTo appliesTo = AppliesTo::Class;
  struct Data {
    const char* memberName = nullptr;
    size_t memberNameSize = 0;
  };
  ReflectAsMember(const Data& data) : memberName(data.memberName, data.memberNameSize) {}
  LOKI_ANNOT_GET_TYPE_ID(ReflectAsMember)
  NameId memberName;
};
template <size_t N>
static constexpr ReflectAsMember::Data reflectAsMember(const char (&memberName)[N]) {
  return {std::define_static_string(memberName), N};
}

}  // namespace loki::core