#pragma once

#include <functional>
#include <memory>

#include "BaseObject.hpp"
#include "TypeInfo.hpp"

namespace loki::core {

class ReflectionFactory {
 public:
  template <class T>
  void registerClass();

  template <class T>
  std::unique_ptr<T> build(const TypeInfo& _typeInfo = getTypeInfo<T>());

 private:
  using Builder = std::function<std::unique_ptr<BaseObject>()>;
  std::unordered_map<std::string_view, Builder> m_builders;
};

}  // namespace loki::core

#include "ReflectionFactory.hxx"
