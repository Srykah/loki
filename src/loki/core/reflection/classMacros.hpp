#pragma once

#include <format>

#include <loki/core/reflection/classMeta.hpp>

#define LOKI_REFLECTION_CLASS_BEGIN_NO_FACTORY(Class) \
  template <>                                         \
  struct loki::core::TypeInfoHolder<Class> {          \
    using CLASSNAME = Class;                          \
    static TypeInfo getTypeInfo() {                   \
      TypeInfo TYPEINFO{.info = ClassInfo{}};         \
      ClassInfo& CLASSINFO = std::get<ClassInfo>(TYPEINFO.info);

#define LOKI_REFLECTION_TEMPLATE_CLASS_BEGIN_NO_FACTORY(TemplateClass) \
  template <class T>                                                   \
  struct loki::core::TypeInfoHolder<TemplateClass<T>> {                \
    using CLASSNAME = TemplateClass<T>;                                \
    static TypeInfo getTypeInfo() {                                    \
      TypeInfo TYPEINFO{.info = ClassInfo{}};                          \
      ClassInfo& CLASSINFO = std::get<ClassInfo>(TYPEINFO.info);

#define LOKI_REFLECTION_TEMPLATE_2_CLASS_BEGIN_NO_FACTORY(TemplateClass) \
  template <class X, class Y>                                            \
  struct loki::core::TypeInfoHolder<TemplateClass<X, Y>> {               \
    using CLASSNAME = TemplateClass<X, Y>;                               \
    static TypeInfo getTypeInfo() {                                      \
      TypeInfo TYPEINFO{.info = ClassInfo{}};                            \
      ClassInfo& CLASSINFO = std::get<ClassInfo>(TYPEINFO.info);

#define LOKI_REFLECTION_CLASS_PARENT(Parent)  \
  CLASSINFO.parentType = getTypeId<Parent>(); \
  CLASSINFO.toParentType = [](void* obj) -> void* { return static_cast<Parent*>(&details::to<CLASS>(obj)); };

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

#define LOKI_REFLECTION_CLASS_BEGIN_CHILD_NO_FACTORY(Child, Parent) \
  LOKI_REFLECTION_CLASS_BEGIN_NO_FACTORY(Child)                     \
  LOKI_REFLECTION_CLASS_PARENT(Parent)

#define LOKI_REFLECTION_CLASS_BEGIN_CHILD(Child, Parent)      \
  LOKI_REFLECTION_CLASS_BEGIN_CHILD_NO_FACTORY(Child, Parent) \
  LOKI_REFLECTION_CLASS_FACTORY(details::getBasicFactory<Child>())

#define LOKI_REFLECTION_CLASS_ANNOTATION(AnnotationType, ...)                                                 \
  static_assert(std::is_base_of_v<loki::core::Annotation, AnnotationType>,                                    \
                "LOKI_REFLECTION_CLASS_ANNOTATION requires a type derived from loki::core::Annotation");      \
  static_assert((AnnotationType::appliesTo & loki::core::Annotation::Class) == loki::core::Annotation::Class, \
                "LOKI_REFLECTION_CLASS_ANNOTATION requires an annotation that applies to classes");           \
  CLASSINFO.annotations.push_back(std::make_unique<AnnotationType>(__VA_ARGS__));

#define LOKI_REFLECTION_CLASS_FIELD_CUSTOM_OFFSET(fieldType, fieldName, fieldOffset) \
  CLASSINFO.fields.emplace_back({.type = fieldType, .name = fieldName, .offset = fieldOffset});

#define LOKI_REFLECTION_CLASS_FIELD_CUSTOM_GETTER(fieldType, fieldName, fieldGetter) \
  CLASSINFO.fields.emplace_back({.type = fieldType, .name = fieldName, .getter = fieldGetter});

#define LOKI_REFLECTION_CLASS_FIELD_CUSTOM_GETTERCONST_SETTER(fieldType, fieldName, fieldGetterConst, fieldSetter) \
  CLASSINFO.fields.emplace_back(                                                                                   \
      {.type = fieldType, .name = fieldName, .getterConst = fieldGetterConst, .setter = fieldSetter});

#define LOKI_REFLECTION_CLASS_FIELD(field) CLASSINFO.fields.emplace_back(getFieldInfo<^^CLASSNAME::field>());

#define LOKI_REFLECTION_CLASS_END() \
  return TYPEINFO;                  \
  }                                 \
  }                                 \
  ;
