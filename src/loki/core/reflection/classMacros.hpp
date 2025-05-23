#pragma once

#include <format>

#include <loki/core/reflection/reflectionUtils.hpp>

#define LOKI_REFLECTION_CLASS_DECLARE(...) friend ::loki::core::TypeInfoHolder<__VA_ARGS__>;

#define LOKI_REFLECTION_CLASS_BEGIN_NO_FACTORY(Class) \
  template <>                                         \
  struct loki::core::TypeInfoHolder<Class> {          \
    static const TypeInfo& getTypeInfo_internal() {   \
      static const TypeInfo TYPEINFO = []() {          \
        TypeInfo TYPEINFO { .info = ClassInfo { .id = #Class } }; \
        ClassInfo& CLASSINFO = std::get<ClassInfo>(TYPEINFO.info); \
        using CLASSNAME = Class;
#define LOKI_REFLECTION_TEMPLATE_CLASS_BEGIN_NO_FACTORY(TemplateClass) \
  template <class T>                                                   \
  struct loki::core::TypeInfoHolder<TemplateClass<T>> {                \
    static const TypeInfo& getTypeInfo_internal() {                    \
      static const TypeInfo TYPEINFO = []() {          \
TypeInfo TYPEINFO { .info = ClassInfo { /* .id = std::format(#TemplateClass "<{}>", std::get<ClassInfo>(getTypeInfo<T>().info).id) */ \
.id = #TemplateClass } };       \
ClassInfo& CLASSINFO = std::get<ClassInfo>(TYPEINFO.info); \
using CLASSNAME = TemplateClass<T>;
#define LOKI_REFLECTION_TEMPLATE_2_CLASS_BEGIN_NO_FACTORY(TemplateClass) \
  template <class X, class Y>                                            \
  struct loki::core::TypeInfoHolder<TemplateClass<X, Y>> {               \
    static const TypeInfo& getTypeInfo_internal() {                      \
      static const TypeInfo TYPEINFO = []() {          \
TypeInfo TYPEINFO {\
  .info = ClassInfo {\
/* .id = std::format(#TemplateClass "<{}, {}>", std::get<ClassInfo>(getTypeInfo<X>().info).id, std::get<ClassInfo>(getTypeInfo<Y>().info).id) */ \
.id = #TemplateClass } };\
ClassInfo& CLASSINFO = std::get<ClassInfo>(TYPEINFO.info); \
using CLASSNAME = TemplateClass<X, Y>;
#define LOKI_REFLECTION_CLASS_PARENT(Class, Parent) \
  CLASSINFO.parentType = &getTypeInfo<Parent>();    \
  CLASSINFO.toParentType = [](void* obj) -> void* { return static_cast<Parent*>(&details::to<Class>(obj)); };

#define LOKI_REFLECTION_CLASS_FACTORY(...) TYPEINFO.factory = __VA_ARGS__;

#define LOKI_REFLECTION_CLASS_BEGIN(Class)      \
  LOKI_REFLECTION_CLASS_BEGIN_NO_FACTORY(Class) \
  LOKI_REFLECTION_CLASS_FACTORY(details::getBasicFactory<Class>())

#define LOKI_REFLECTION_TEMPLATE_CLASS_BEGIN(TemplateClass)      \
  LOKI_REFLECTION_TEMPLATE_CLASS_BEGIN_NO_FACTORY(TemplateClass) \
  LOKI_REFLECTION_CLASS_FACTORY(details::getBasicFactory<TemplateClass<T>>())

#define LOKI_REFLECTION_TEMPLATE_2_CLASS_BEGIN(TemplateClass)      \
  LOKI_REFLECTION_TEMPLATE_2_CLASS_BEGIN_NO_FACTORY(TemplateClass) \
  LOKI_REFLECTION_CLASS_FACTORY(details::getBasicFactory<TemplateClass<X, Y>>())

#define LOKI_REFLECTION_CLASS_BEGIN_CHILD(Parent, Child) \
  LOKI_REFLECTION_CLASS_BEGIN(Child)                     \
  LOKI_REFLECTION_CLASS_PARENT(Child, Parent)

#define LOKI_REFLECTION_CLASS_ATTRIBUTE(AttributeType, ...) \
  CLASSINFO.attributes.push_back(std::make_unique<AttributeType>(__VA_ARGS__));

#define LOKI_REFLECTION_CLASS_FIELD_CUSTOM(fieldType, fieldName, isFieldInPlace, fieldGetter, fieldGetterConst, \
                                           fieldSetter)                                                         \
  CLASSINFO.fields.emplace_back(fieldType, fieldName, isFieldInPlace, fieldGetter, fieldGetterConst, fieldSetter);

#define LOKI_REFLECTION_CLASS_FIELD(field)                                                                           \
  LOKI_REFLECTION_CLASS_FIELD_CUSTOM(                                                                                \
      getTypeInfo<decltype(CLASSNAME::field)>(), #field, true,                                                       \
      [](void* obj) -> TmpObj { return TmpObj::fromPtrNonOwned(details::from(details::to<CLASSNAME>(obj).field)); }, \
      [](const void* obj) -> ConstTmpObj {                                                                           \
        return ConstTmpObj::fromPtrNonOwned(details::from(details::to<CLASSNAME>(obj).field));                       \
      },                                                                                                             \
      [](void* obj, void* data) -> void {                                                                            \
        auto& field = details::to<CLASSNAME>(obj).field;                                                             \
        auto& newValue = details::to<decltype(CLASSNAME::field)>(data);                                              \
        if (&newValue != &field)                                                                                     \
          field = std::move(newValue);                                                                               \
      })

#define LOKI_REFLECTION_CLASS_END() \
  return TYPEINFO;                  \
  }                                 \
  ();                               \
  return TYPEINFO;                  \
  }                                 \
  }                                 \
  ;
