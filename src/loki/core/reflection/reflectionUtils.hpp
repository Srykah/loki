#pragma once

#include <cassert>
#include <meta>

#include <loki/core/utils/TmpObj.hpp>

namespace loki::core::details {

template <class T>
Factory getBasicFactory() {
  return [](void*, TmpObj::Ownership ownership) -> TmpObj {
    if (ownership == TmpObj::Ownership::NonOwned)
      return TmpObj::makeNonOwned<T>();
    return TmpObj::makeOwned<T>();
  };
}

template <class T>
const T& to(const void* obj) {
  return *static_cast<const T*>(obj);
}

template <class T>
const void* from(const T& obj) {
  return static_cast<const void*>(&obj);
}

template <class T>
T& to(void* obj) {
  return *static_cast<T*>(obj);
}

template <class T>
void* from(T& obj) {
  return static_cast<void*>(&obj);
}

}  // namespace loki::core::details

namespace loki::core {

struct ReflectAnnotation {};

template <std::meta::info stuffMeta>
consteval bool hasReflectAnnotation() {
  static constexpr auto annotsMeta =
      std::define_static_array(std::meta::annotations_of_with_type(stuffMeta, ^^ReflectAnnotation));
  return !annotsMeta.empty();
}

template <class T>
concept Reflected = hasReflectAnnotation<^^T>();

using TypeId = std::string;

template <std::meta::info classOrNamespaceMeta>
TypeId getTypeId() {
  static constexpr auto parentMeta = std::meta::parent_of(classOrNamespaceMeta);
  if constexpr (parentMeta == ^^::) {
    return TypeId{std::meta::identifier_of(classOrNamespaceMeta)};
  } else {
    return getTypeId<parentMeta>() + "::" + std::meta::identifier_of(classOrNamespaceMeta);
  }
}

}  // namespace loki::core

namespace loki {
loki::core::ReflectAnnotation reflect;  // put it in the outer namespace for readability
}  // namespace loki
