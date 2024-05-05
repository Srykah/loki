#pragma once

#include <loki/core/reflection/TypeInfo.hpp>

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