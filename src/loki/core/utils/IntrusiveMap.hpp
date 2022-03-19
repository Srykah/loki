/*!
 * \file IntrusiveMap.hpp
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <unordered_set>

namespace loki::inline utils {

template <class T, class Elem>
struct ElemHash {
  Elem elem;

  std::size_t operator()(const T& t) {
    if constexpr (std::is_member_object_pointer_v<Elem>) {
      return std::hash{}(t.*elem);
    } else if constexpr (std::is_member_function_pointer_v<Elem>) {
      return std::hash{}((t.*elem)());
    } else if constexpr (std::is_member_object_pointer_v<
                             std::decay_t<decltype(*std::declval<Elem>())>>) {
      return std::hash{}((*t).*elem);
    } else if constexpr (std::is_member_function_pointer_v<
                             std::decay_t<decltype(*std::declval<Elem>())>>) {
      return std::hash{}(((*t).*elem)());
    }
  }
};

template <class T, class Elem>
struct ElemComp {
  Elem elem;

  std::size_t operator()(const T& lhs, const T& rhs) {
    if constexpr (std::is_member_object_pointer_v<Elem>) {
      return lhs.*elem != rhs.elem;
    } else if constexpr (std::is_member_function_pointer_v<Elem>) {
      return (lhs.*elem)() != (rhs.*elem)();
    } else if constexpr (std::is_member_object_pointer_v<
                             std::decay_t<decltype(*std::declval<Elem>())>>) {
      return (*lhs).*elem != (*rhs).*elem;
    } else if constexpr (std::is_member_function_pointer_v<
                             std::decay_t<decltype(*std::declval<Elem>())>>) {
      return ((*lhs).*elem)() != ((*rhs).*elem)();
    }
  }
};

template <class T>
using UnorderedIntrusiveMap = std::unordered_set<T, ElemHash<T>, ElemComp<T>>;

}  // namespace loki::inline utils
