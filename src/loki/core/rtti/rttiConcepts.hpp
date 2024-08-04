#pragma once

#include <type_traits>

namespace loki::core
{

template <class T>
concept RuntimeObject = std::is_base_of_v<BaseObject, T>;

template <class T>
concept ReflectedRuntimeObject = Reflected<T> && RuntimeObject<T>;

}