#pragma once

#include <loki/core/reflection/basicTypesInfo.hpp>
#include <loki/core/reflection/reflectionUtils.hpp>

#define LOKI_REFLECTION_ENUM_BEGIN(Enum)            \
  template <>                                       \
  struct loki::core::TypeInfoHolder<Enum> {         \
    static const TypeInfo& getTypeInfo_internal() { \
      static const TypeInfo TYPEINFO = []() {          \
TypeInfo TYPEINFO {\
.factory = details::getBasicFactory<Enum>(), \
.info = EnumInfo { .backingType = std::get<IntegerInfo>(getTypeInfo<std::underlying_type_t<Enum>>().info) } }; \
EnumInfo& ENUMINFO = std::get<EnumInfo>(TYPEINFO.info);
#define LOKI_REFLECTION_ENUMERATOR(Enum, Enumerator) \
  ENUMINFO.enumerators.emplace_back(#Enumerator, static_cast<std::int64_t>(Enum::Enumerator));

#define LOKI_REFLECTION_ENUM_END() \
  return TYPEINFO;                 \
  }                                \
  ();                              \
  return TYPEINFO;                 \
  }                                \
  }                                \
  ;
