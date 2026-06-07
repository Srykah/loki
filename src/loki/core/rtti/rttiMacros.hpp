#pragma once

#define LOKI_RTTI_CLASS_DECLARE() \
 public:                          \
  const ::loki::core::TypeInfo& getTypeInfo() const override;

#define LOKI_RTTI_CLASS_DEFINE(Class)                        \
  const ::loki::core::TypeInfo& Class::getTypeInfo() const { \
    return ::loki::getTypeInfo<Class>();                     \
  }

#define LOKI_RTTI_CLASS_DEFINE_INLINE(Class) inline LOKI_RTTI_CLASS_DEFINE(Class)
