#pragma once

#include <loki/core/reflection/classMacros.hpp>

#define LOKI_RTTI_CLASS_DECLARE_NO_REFLECTION() \
 public:                                        \
  const ::loki::core::TypeInfo& getClassTypeInfo() const override;

#define LOKI_RTTI_CLASS_DECLARE(Class) \
  LOKI_REFLECTION_CLASS_DECLARE(Class) \
  LOKI_RTTI_CLASS_DECLARE_NO_REFLECTION()

#define LOKI_RTTI_CLASS_DEFINE(Class)                                    \
  inline const ::loki::core::TypeInfo& Class::getClassTypeInfo() const { \
    return ::loki::core::getTypeInfo<Class>();                           \
  }
