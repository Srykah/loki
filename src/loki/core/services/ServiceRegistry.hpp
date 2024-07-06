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
  T& get() const;

  static void setInstance(const ServiceRegistry* instance);
  static const ServiceRegistry& getInstance();

 private:
  static const ServiceRegistry* s_instance;

  std::unordered_map<core::ClassId, core::BaseObject*> services;
};

}  // namespace loki::system

// shortcut
namespace loki {
template <core::ReflectedRuntimeObject T>
T& getService();
}  // namespace loki

#include "ServiceRegistry.hxx"
