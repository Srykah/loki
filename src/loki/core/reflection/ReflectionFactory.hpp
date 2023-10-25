#pragma once

#include <functional>
#include <memory>

#include "BaseObject.hpp"
#include "TypeInfo.hpp"

namespace loki::core {

template <class T>
concept RTTIObject = std::is_base_of_v<BaseObject, T>;

class ReflectionFactory {
 public:
  using Builder = std::function<BaseObject*()>;

  template <RTTIObject T>
  void registerClass();

  template <RTTIObject T>
  void registerClass(Builder&& builder);

  template <RTTIObject T>
  std::unique_ptr<T> build(std::string_view realClassName);

 private:
  std::unordered_map<std::string_view, Builder> builders;
};

}  // namespace loki::core

#include "ReflectionFactory.hxx"
