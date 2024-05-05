#pragma once

#include <loki/core/reflection/reflectionUtils.hpp>

#define LOKI_REFLECTION_ENUM_BEGIN(Enum, BackingType) \
  template <>                                         \
  struct ::loki::core::TypeInfoHolder<Enum> {         \
    static const TypeInfo& getTypeInfo_internal() {   \
      static const TypeInfo TYPEINFO = []() {          \
TypeInfo TYPEINFO {\
.factory = details::getBasicFactory<Enum>(), \
.info = EnumInfo { .backingType = std::get<IntegerInfo>(getTypeInfo<BackingType>().info) } }; \
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