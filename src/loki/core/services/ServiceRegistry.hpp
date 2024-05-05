#pragma once

#include <unordered_map>

#include <loki/core/reflection/TypeInfo.hpp>
#include <loki/core/runtimeObject/BaseObject.hpp>

namespace loki::system {

class ServiceRegistry {
 public:
  ServiceRegistry();

  template <core::ReflectedRuntimeObject T>
  bool registerService(T& service);

  template <core::ReflectedRuntimeObject T>
  static T& get();

 private:
  inline static const ServiceRegistry* s_instance = nullptr;

 private:
  std::unordered_map<const core::TypeInfo*, core::BaseObject*> services;
};

}  // namespace loki::system

// shortcut
namespace loki {
template <core::ReflectedRuntimeObject T>
T& getService();
}  // namespace loki

#include "ServiceRegistry.hxx"
